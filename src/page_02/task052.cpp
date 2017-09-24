#include <limits>

#include "base/digit_manipulation.h"
#include "base/task.h"
#include "gtest/gtest.h"

TEST(Task52, InputData) {
  EXPECT_EQ(GetDigitMultiSet(125874), GetDigitMultiSet(125874 * 2));
}

TASK(52) {
  uint64_t x = 1;

  while (x != std::numeric_limits<decltype(x)>::max()) {
    ++x;
    auto basic_set = GetDigitMultiSet(x);
    if (basic_set == GetDigitMultiSet(2 * x) &&
        basic_set == GetDigitMultiSet(3 * x) &&
        basic_set == GetDigitMultiSet(4 * x) &&
        basic_set == GetDigitMultiSet(5 * x) &&
        basic_set == GetDigitMultiSet(6 * x)) {
      return x;
    }
  }

  return -1;
}
