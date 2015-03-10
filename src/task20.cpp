#include <gmpxx.h>

#include "base/task.h"
#include "gtest/gtest.h"

uint DigitSum(const mpz_class &number) {
  mpz_class num = number;
  uint sum = 0;
  while (num != 0) {
    unsigned long digit = mpz_tdiv_q_ui(num.get_mpz_t(), num.get_mpz_t(), 10);
    sum += digit;
  }

  return sum;
};

TEST(Task20, DigitSum) {
  mpz_class a;
  a = "1234567890";
  EXPECT_EQ(45, DigitSum(a));
}

TASK(20) {
  mpz_class factorial = 1;

  for (int i = 1; i <= 100; ++i) {
    factorial *= i;
  }

  SetResult(ToString(DigitSum(factorial)));
}
