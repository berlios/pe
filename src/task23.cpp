#include <gmpxx.h>
#include <set>

#include "base/number_theory.h"
#include "base/task.h"
#include "gtest/gtest.h"

bool IsAbundant(const mpz_class &num) {
  return SumOfProperDivisors(num) > num;
};

TEST(Task23, IsAbundant) {
  EXPECT_TRUE(IsAbundant(12));
}

TASK(23) {
  std::set<int> abundant_numbers;

  for (int i = 2; i <= 28123; ++i) {
    if (IsAbundant(i)) {
      abundant_numbers.emplace(i);
    }
  }


  int res = 0;
  for (int i = 28123; i > 0; --i) {
    bool found = false;
    for (auto num : abundant_numbers) {
      if (abundant_numbers.find(i - num) != abundant_numbers.end()) {
        found = true;
        break;
      }
    }

    if (!found) {
      res += i;
    }
  }

  SetResult(ToString(res));
}
