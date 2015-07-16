#include "base/digit_manipulation.h"

#include "base/task.h"
#include "gtest/gtest.h"

// Returns n-th digit of the fractional part of Champernowne's constant.
int ChampernowneDigit(uint n) {
  uint length = 1, power_of_ten = 1;

  // In the task n <= 10^6 so overflow is not a problem.
  while (9*power_of_ten*length < n) {
    n -= 9*power_of_ten*length;
    length++;
    power_of_ten *= 10;
  }

  uint t = (n - 1) / length;
  uint s = power_of_ten + t;

  return NthDigit(s, (n - 1) % length + 1);
}

TEST(Task40, ChampernowneDigit) {
  EXPECT_EQ(1, ChampernowneDigit(12));
  EXPECT_EQ(2, ChampernowneDigit(15));
}

TASK(40) {
  int prod = 1;
  for (int i = 1; i <= 1000*1000; i *= 10) {
    prod *= ChampernowneDigit(i);
  }

  return prod;
}
