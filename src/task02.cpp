#include <vector>

#include "base/common.h"
#include "base/task.h"

using std::vector;

static int main_func() {
  vector<int> fibs;

  fibs.push_back(1);
  fibs.push_back(1);
  int last_fib = 1;

  while (last_fib < 4*1000*1000) {
    int m = fibs[fibs.size() - 1];  // last elem
    int n = fibs[fibs.size() - 2];  // element before last one
    fibs.push_back(n + m);
    last_fib = n + m;
  }

  // Remove the only fibonacci number in sequence that is greater
  // than 4 million.
  fibs.pop_back();

  int sum = 0;
  for (size_t i = 0; i < fibs.size(); ++i) {
    // Even fibonacci numbers have their index in the form 2+3k
    if (i%3 == 2) {
      sum += fibs[i];
    }
  }

  return sum;
}

TASK(2) {
  return main_func();
}
