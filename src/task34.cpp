#include "base/task.h"
#include "gtest/gtest.h"

uint Factorial(uint n) {
  if (n == 0 || n == 1) {
    return 1;
  }

  return Factorial(n - 1)*n;
}

uint SumOfDigitFactorials(uint n) {
  uint sum = 0;
  while (n > 0) {
    sum += Factorial(n % 10);
    n = n /10;
  }

  return sum;
}

TEST(Task34, SumOfDigitFactorials) {
  EXPECT_EQ(145, SumOfDigitFactorials(145));
}

TASK(34) {
  uint sum = 0;
  for (uint i = 3; i < 10*1000*1000; ++i) {
    if (i == SumOfDigitFactorials(i)) {
      sum += i;
    }
  }

  return sum;
}
