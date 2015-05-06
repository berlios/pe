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

TEST(LengthOfRepeatingCycle, BasicTest) {
  EXPECT_EQ(0, LengthOfRepeatingCycle(mpq_class(1, 2)));
  EXPECT_EQ(1, LengthOfRepeatingCycle(mpq_class(1, 3)));
  EXPECT_EQ(0, LengthOfRepeatingCycle(mpq_class(7, 14)));
  EXPECT_EQ(6, LengthOfRepeatingCycle(mpq_class(1, 7)));
  EXPECT_EQ(6, LengthOfRepeatingCycle(mpq_class(21, 49)));
  EXPECT_EQ(16, LengthOfRepeatingCycle(mpq_class(1, 17)));
}
