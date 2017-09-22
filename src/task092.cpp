#include "base/task.h"

namespace {
int SumOfSquaresOfDigits(int n) {
  int result = 0;
  while (n > 0) {
    result += (n % 10) * (n % 10);
    n /= 10;
  }
  return result;
}
}

TASK(92) {
  int counter = 0;
  for (int i = 1; i < 10*1000*1000; ++i) {
    int n = i;
    while (n != 1 && n != 89) {
      n = SumOfSquaresOfDigits(n);
    }
    if (n == 89) {
      counter++;
    }
  }
  return counter;
}
