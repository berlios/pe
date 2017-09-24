#include <algorithm>

#include "base/macros.h"
#include "base/number_theory.h"
#include "base/quadratic_rational.h"
#include "base/task.h"
#include "gtest/gtest.h"

int GetContinuedFractionPeriod(int n) {
  std::vector<QuadraticRational> fractions;
  fractions.emplace_back(n, 1, 0);

  while (true) {
    QuadraticRational f = fractions.back();
    f -= f.Floor();
    f = f.Reciprocal();
    auto it = std::find(fractions.rbegin(), fractions.rend(), f);
    if (it == fractions.rend()) {
      fractions.emplace_back(f);
      continue;
    }

    return std::distance(fractions.rbegin(), it) + 1;
  }
}

TEST(Task64, GetContinuedFractionPeriod) {
  EXPECT_EQ(1, GetContinuedFractionPeriod(2));
  EXPECT_EQ(2, GetContinuedFractionPeriod(3));
}

TASK(64) {
  int counter = 0;
  for (int i = 2; i <= 10000; ++i) {
    if (IsSquareNumber(i)) {
      continue;
    }
    if (GetContinuedFractionPeriod(i) % 2 == 1) {
      counter++;
    }
  }
  return counter;
}
