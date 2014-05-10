#include "base/task.h"

#include <algorithm>
#include <string>
#include <vector>

namespace euler {

Task::~Task() {}

void Task::SetResult(const std::string &str) {
  result_ = str;
}

const std::string& Task::result() {
  return result_;
}

std::string Task::CloneResult() {
  return result_;
}

Task::Task() {}

inline OneClassImpl* GetOneClassImpl() {
  return OneClass::GetInstance()->impl();
}

TaskInfo* MakeAndRegisterTaskInfo(int task_num,
                                  TaskFactoryBase *factory) {
  TaskInfo *task_info = new TaskInfo(task_num, factory);
  GetOneClassImpl()->AddTaskInfo(task_info);
  return task_info;
}

TaskInfo::~TaskInfo() {
  delete factory_;
}

int TaskInfo::task_num() const {
  return task_num_;
}

TaskInfo::TaskInfo(int task_num, euler::TaskFactoryBase *factory)
    : task_num_(task_num),
      factory_(factory) {}

void TaskInfo::Run() {
  Task *task = factory_->CreateTask();
  task->TaskBody();
  result_ = task->CloneResult();
  delete task;
}

OneClass *OneClass::GetInstance() {
  static OneClass instance;
  return &instance;
}

void OneClass::Run(int task_num) {
  impl_->Run(task_num);
}

void OneClass::RunBiggestNumber() {
  int n = impl_->GetMax();
  Run(n);
}

const std::string &OneClass::GetLastResult() {
  return impl_->GetLastResult();
}

OneClass::OneClass() {
  impl_ = new OneClassImpl;
}

OneClass::~OneClass() {
  delete impl_;
}

OneClassImpl::OneClassImpl() : index_of_last_solved_task_(-1) {}

OneClassImpl::~OneClassImpl() {}

void OneClassImpl::AddTaskInfo(TaskInfo *task_info) {
  tasks_.push_back(task_info);
}

const std::string& OneClassImpl::GetLastResult() const {
  return tasks_[index_of_last_solved_task_]->result_;
}

// bool Cmp(std::vector<TaskInfo*>::iterator first,
//          std::vector<TaskInfo*>::iterator second) {
//   return (*first)->task_num() < (*second)->task_num();
// }

bool Cmp(TaskInfo *first, TaskInfo *second) {
  return first->task_num() < second->task_num();
}

int OneClassImpl::GetMax() {
  TaskInfo *max_elem = *std::max_element(tasks_.begin(), tasks_.end(), Cmp);

  return max_elem->task_num();
}

class TaskNumIs {
public:
  explicit TaskNumIs(int n) : task_num_(n) {}

  bool operator()(const TaskInfo* task_info) const {
    return task_info != NULL && task_info->task_num() == task_num_;
  }
private:
  int task_num_;
};

void OneClassImpl::Run(int task_num) {
  const std::vector<TaskInfo*>::const_iterator task_info =
      std::find_if(tasks_.begin(), tasks_.end(), TaskNumIs(task_num));

  // Save index for future.
  index_of_last_solved_task_ = task_info - tasks_.begin();
  (*task_info)->Run();
}
}
