#include "base/number_theory.h"

#include "gtest/gtest.h"

TEST(Task21, SumOfDivisors) {
  mpz_class a = 8;
  EXPECT_EQ(15, SumOfAllDivisors(a));
  EXPECT_EQ(7, SumOfProperDivisors(a));

  a = 24;
  EXPECT_EQ(60, SumOfAllDivisors(a));
  EXPECT_EQ(36, SumOfProperDivisors(a));

  a = 3;
  EXPECT_EQ(4, SumOfAllDivisors(a));
  EXPECT_EQ(1, SumOfProperDivisors(a));
}

TEST(Task21, Numbers220And284AreAmicable) {
  EXPECT_EQ(284, SumOfProperDivisors(220));
  EXPECT_EQ(220, SumOfProperDivisors(284));
}
