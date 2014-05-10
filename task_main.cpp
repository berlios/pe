#include "base/task.h"

#include <cstdio>

int main() {
//   int task_num;
//   scanf("%d", &task_num);

  // Maybe it would be better to hide it in some function.
  // ::euler::OneClass::GetInstance()->Run(task_num);
  ::euler::OneClass::GetInstance()->RunBiggestNumber();
  printf("The answer to task #biggest: %s\n",
         ::euler::OneClass::GetInstance()->GetLastResult().c_str());
}
