#include <set>

#include "base/task.h"
#include "gtest/gtest.h"

typedef std::set<int> DigitSet;

DigitSet GetDigitSet(uint num) {
  DigitSet ret;

  while (num > 0) {
    ret.insert(num % 10);
    num = num / 10;
  }

  return ret;
}

uint DigitCount(uint num) {
  uint k = 0;
  uint power_of_ten = 1;

  while (num / power_of_ten > 0) {
    k++;
    power_of_ten *= 10;
  }

  return k;
}

TEST(Task32, DigitSet) {
  DigitSet digits = GetDigitSet(12344);
  ASSERT_EQ(4, digits.size());
  EXPECT_NE(digits.end(), digits.find(1));
  EXPECT_NE(digits.end(), digits.find(2));
  EXPECT_NE(digits.end(), digits.find(3));
  EXPECT_NE(digits.end(), digits.find(4));

  EXPECT_EQ(4, DigitCount(4067));
}

TASK(32) {
  DigitSet digits_of_i, digits_of_j, digits_of_product, all_digits;
  std::set<uint> results;
  for (uint i = 1; i < 10000; ++i) {
    for (uint j = 1; j < 10000; ++j) {
      digits_of_i = GetDigitSet(i);
      digits_of_j = GetDigitSet(j);
      digits_of_product = GetDigitSet(i*j);
      all_digits = digits_of_i;
      all_digits.insert(digits_of_j.begin(), digits_of_j.end());
      all_digits.insert(digits_of_product.begin(), digits_of_product.end());

      if (DigitCount(i) + DigitCount(j) + DigitCount(i*j) == 9 &&
          all_digits.size() == 9 &&
          all_digits.find(0) == all_digits.end()) {
        results.insert(i*j);
      }
    }
  }

  uint sum = 0;
  for (auto element : results) {
    sum += element;
  }
  SetResult(ToString(sum));
}
