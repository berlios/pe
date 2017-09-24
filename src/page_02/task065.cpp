#include "base/continued_fraction.h"
#include "base/digit_manipulation.h"
#include "base/task.h"
#include "gtest/gtest.h"

// n is assumed >= 1.
std::vector<int> GetSequenceOfEUpTo(int n) {
  std::vector<int> result{2};

  int counter = 2;
  for (int i = 0; i < n - 1; ++i) {
    if (i % 3 == 1) {
      result.push_back(counter);
      counter += 2;
    } else {
      result.push_back(1);
    }
  }

  return result;
}

TEST(Task65, SumOfDigitsIn10thConvergent) {
  mpq_class convergent_10 =
      FiniteNumberSequenceToFraction(GetSequenceOfEUpTo(10));
  EXPECT_EQ(17u, DigitSum(convergent_10.get_num()));
}

TASK(65) {
  mpq_class convergent_100 =
      FiniteNumberSequenceToFraction(GetSequenceOfEUpTo(100));
  return DigitSum(convergent_100.get_num());
}
