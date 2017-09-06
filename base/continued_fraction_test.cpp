#include "base/continued_fraction.h"

#include "gtest/gtest.h"

TEST(ContinuedFraction, FiniteNumberSequenceToFraction) {
  std::vector<int> sequence = {1, 2};
  EXPECT_EQ(mpq_class(3, 2), FiniteNumberSequenceToFraction(sequence));

  sequence.push_back(2);
  EXPECT_EQ(mpq_class(7, 5), FiniteNumberSequenceToFraction(sequence));

  sequence.push_back(2);
  EXPECT_EQ(mpq_class(17, 12), FiniteNumberSequenceToFraction(sequence));

  sequence.push_back(2);
  EXPECT_EQ(mpq_class(41, 29), FiniteNumberSequenceToFraction(sequence));

  sequence.push_back(2);
  EXPECT_EQ(mpq_class(99, 70), FiniteNumberSequenceToFraction(sequence));

  sequence.push_back(2);
  EXPECT_EQ(mpq_class(239, 169), FiniteNumberSequenceToFraction(sequence));

  sequence.push_back(2);
  EXPECT_EQ(mpq_class(577, 408), FiniteNumberSequenceToFraction(sequence));

  sequence.push_back(2);
  EXPECT_EQ(mpq_class(1393, 985), FiniteNumberSequenceToFraction(sequence));
}
