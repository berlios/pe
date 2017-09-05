#ifndef BASE_MACROS_H_
#define BASE_MACROS_H_

#define CHECK(x)                                                \
  do {                                                          \
    if (!(x)) {                                                 \
      printf("%s:%d: Error in function %s", __FILE__, __LINE__, \
             __PRETTY_FUNCTION__);                              \
      abort();                                                  \
    }                                                           \
  } while (false)

#define NOT_IMPLEMENTED() CHECK(false)

#ifdef NDEBUG
#define DCHECK(x) CHECK(true)
#else
#define DCHECK(x) CHECK(x)
#endif

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
  ClassName(const ClassName&) = delete;     \
  ClassName& operator=(const ClassName&) = delete

#endif  // BASE_MACROS_H_

