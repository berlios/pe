#include <gmpxx.h>
#include <vector>

#include "base/continued_fraction.h"
#include "base/number_theory.h"
#include "base/quadratic_rational.h"
#include "base/task.h"
#include "gtest/gtest.h"

std::pair<mpz_class, mpz_class> FundamentalSolutionToPellEquation(int d) {
  QuadraticRational t(d, 1, 0);
  std::vector<int> sequence;

  while (true) {
    int floor = t.Floor().get_si();
    sequence.push_back(floor);

    t -= t.Floor();
    t = t.Reciprocal();

    mpq_class convergent = FiniteNumberSequenceToFraction(sequence);
    if (convergent.get_num() * convergent.get_num() -
            convergent.get_den() * convergent.get_den() * d ==
        1) {
      return {convergent.get_num(), convergent.get_den()};
    }
  }
}

TEST(Task66, FundamentalSolutionToPellEquation) {
  EXPECT_EQ(std::make_pair(3_mpz, 2_mpz), FundamentalSolutionToPellEquation(2));
  EXPECT_EQ(std::make_pair(9_mpz, 4_mpz), FundamentalSolutionToPellEquation(5));
  EXPECT_EQ(std::make_pair(649_mpz, 180_mpz),
            FundamentalSolutionToPellEquation(13));
}

TASK(66) {
  mpz_class maximum_x;
  int corresponding_d = -1;
  for (int d = 2; d <= 1000; ++d) {
    if (IsSquareNumber(d)) {
      continue;
    }

    mpz_class x = FundamentalSolutionToPellEquation(d).first;

    if (maximum_x < x) {
      maximum_x = x;
      corresponding_d = d;
    }
  }

  return corresponding_d;
}
