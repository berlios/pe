// Most of this file was inspired by Google's test framework.

#ifndef BASE_TASK_H_
#define BASE_TASK_H_

#include <gmpxx.h>
#include <string>
#include <vector>

#include "base/macros.h"

namespace euler {

class Task {
 public:
  class Result {
   public:
    Result() { }
    Result(const std::string &str) : result_string_(str) { }
    Result(std::string &&str) : result_string_(std::move(str)) { }
    Result(const mpz_class &num) : result_string_(num.get_str()) { }

    Result(signed char c) : result_string_(1, c) { }
    Result(unsigned char c) : result_string_(1, c) { }

#define IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(ClassName, Type) \
  ClassName(Type n) : result_string_(std::to_string(n)) { }

    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, unsigned int)
    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, signed int)
    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, unsigned long int)
    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, signed long int)
    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, unsigned long long int)
    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, signed long long int)
    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, float)
    IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER(Result, double)

#undef IMPLICIT_CONSTRUCTOR_FROM_A_NUMBER

    std::string ToString() const { return result_string_; }
   private:
    std::string result_string_;
  };

  virtual ~Task();
//   void SetResult(const std::string &str);
  const Result& result();
  std::string GetResultString();

 protected:
  Task();

 private:
  friend class TaskInfo;

  // Rather than just leaving TaskBody() method to run a task,  maybe it would
  // be better to create separate Run() method?
  virtual Result TaskBody() = 0;

  Result result_;
  DISALLOW_COPY_AND_ASSIGN(Task);
};

class TaskFactoryBase {
 public:
  virtual ~TaskFactoryBase() {}
  virtual Task* CreateTask() = 0;

 protected:
  TaskFactoryBase() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(TaskFactoryBase);
};

template<class TaskClass>
class TaskFactoryImpl : public TaskFactoryBase {
 public:
  virtual Task* CreateTask() {return new TaskClass;}
};

class TaskInfo {
 public:
  ~TaskInfo();
  int task_num() const;

 private:
  friend TaskInfo* MakeAndRegisterTaskInfo(int task_num,
                                           TaskFactoryBase *factory);

  friend class OneClassImpl;
  // TaskInfo owns factory after this and is responsible for deleting it.
  TaskInfo(int task_num, TaskFactoryBase *factory);

  // TaskInfo creates task object, runs, and then deletes it.
  void Run();
  const int task_num_;
  std::string result_;
  TaskFactoryBase* const factory_;
  DISALLOW_COPY_AND_ASSIGN(TaskInfo);
};

class OneClassImpl;

// OneClass to rule them all. OneClass to find them.
// OneClass to bring them all and in the patterns bind them.
class OneClass {
 public:
  // This is a singleton class. When this method is called first time,
  // it creates new OneClass object. On the following calls returns
  // pointer to that object.
  static OneClass* GetInstance();
  void Run(int task_num);
  void RunBiggestNumber();
  const std::string& GetLastResult() const;
  int GetNumberOfLastTask() const;

 private:
  friend OneClassImpl* GetOneClassImpl();

  OneClassImpl* impl() {return impl_;}
  const OneClassImpl* impl() const {return impl_;}
  OneClass();
  ~OneClass();

  OneClassImpl *impl_;
  DISALLOW_COPY_AND_ASSIGN(OneClass);
};

class OneClassImpl {
 public:
  OneClassImpl();
  ~OneClassImpl();
  void AddTaskInfo(TaskInfo *task_info);
  void Run(int task_num);
  const std::string& GetLastResult() const;
  int GetNumberOfLastTask() const;
  int GetMax();

 private:
  std::vector<TaskInfo*> tasks_;

  // Task numbers go here. E.g. if we add task #2 then
  // this vector will store 2.
  // std::vector<int> task_numbers_;

  // Record index of last solved task in vector tasks_.
  int index_of_last_solved_task_;
  DISALLOW_COPY_AND_ASSIGN(OneClassImpl);
};

TaskInfo* MakeAndRegisterTaskInfo(int task_num,
                                  TaskFactoryBase *factory);

}  // namespace euler

#define TASK_CLASS_NAME(basic_name, task_num)\
  basic_name##task_num

#define TASK(task_num)                                                  \
class TASK_CLASS_NAME(Task, task_num) : public ::euler::Task {          \
 public:                                                                \
  TASK_CLASS_NAME(Task, task_num)() {}                                  \
 private:                                                               \
  virtual ::euler::Task::Result TaskBody();                                              \
  static ::euler::TaskInfo* const task_info_;                           \
};                                                                      \
                                                                        \
::euler::TaskInfo* const TASK_CLASS_NAME(Task,  task_num)               \
  ::task_info_ =                                                        \
    ::euler::MakeAndRegisterTaskInfo(                                   \
        task_num,                                                       \
        new ::euler::TaskFactoryImpl<TASK_CLASS_NAME(Task, task_num)>); \
::euler::Task::Result TASK_CLASS_NAME(Task, task_num)::TaskBody()

#endif  // BASE_TASK_H_
