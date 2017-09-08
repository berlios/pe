#include "base/quadratic_rational.h"

#include "gtest/gtest.h"

TEST(QuadraticRational, BasicTest) {
  QuadraticRational n(23, 1, 0);

  EXPECT_EQ(4, n.Floor());
  EXPECT_EQ(QuadraticRational(23, mpq_class(1, 23), 0), n.Reciprocal());

  n -= 4;
  EXPECT_EQ(QuadraticRational(23, mpq_class(1, 7), mpq_class(4, 7)),
            n.Reciprocal());
  EXPECT_EQ(1, n.Reciprocal().Floor());
}
