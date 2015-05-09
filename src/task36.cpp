#include <algorithm>
#include <gmpxx.h>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

mpz_class ReverseInBase(const mpz_class &num, uint base) {
  std::string str = num.get_str(base);
  std::reverse(str.begin(), str.end());

  return mpz_class(str, base);
}

mpz_class Reverse(const mpz_class &num) {
  return ReverseInBase(num, 10);
}

TEST(Task36, Reverse) {
  EXPECT_EQ(0, Reverse(0));
  EXPECT_EQ(6, Reverse(6));
  EXPECT_EQ(45689, Reverse(98654));

  // 585 in base 10 = 1001001001 in base 2.
  EXPECT_EQ(585, ReverseInBase(585, 2));
}

TASK(36) {
  uint sum = 0;

  for (uint i = 1; i < 1000*1000; ++i) {
    if (i == ReverseInBase(i, 10) && i == ReverseInBase(i, 2)) {
      sum += i;
    }
  }

  SetResult(ToString(sum));
}
