#include <gmpxx.h>
#include <map>

#include "base/number_theory.h"
#include "base/task.h"
#include "gtest/gtest.h"

TEST(Task21, Numbers220And284AreAmicable) {
  EXPECT_EQ(284, SumOfProperDivisors(220));
  EXPECT_EQ(220, SumOfProperDivisors(284));
}

TASK(21) {
  int sum = 0;

  for (int i = 2; i < 10000; ++i) {
    mpz_class pair = SumOfProperDivisors(i);
    if (pair < 10000 && i != pair && i == SumOfProperDivisors(pair)) {
      printf("%d\n", i);
      sum += i;
    }
  }

  return sum;
}
