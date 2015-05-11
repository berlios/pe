#include <algorithm>
#include <gmpxx.h>
#include <vector>

#include "base/digit_manipulation.h"
#include "base/task.h"
#include "gtest/gtest.h"

std::vector<uint> MultiplyEachElement(const std::vector<uint> &vec,
                                      uint coefficient) {
  auto copy = vec;
  for (auto &number : copy) {
    number *= coefficient;
  }

  return copy;
}

std::string ConcatenateNumbersAsStrings(const std::vector<uint> &vec) {
  std::string result;
  for (auto number : vec) {
    result.append(ToString(number));
  }

  return result;
}

TEST(Task38, MultiplyEachElement) {
  std::vector<uint> vec{1, 2, 3, 6};
  vec = MultiplyEachElement(vec, 5);
  ASSERT_EQ(4, vec.size());
  EXPECT_EQ(5, vec[0]);
  EXPECT_EQ(10, vec[1]);
  EXPECT_EQ(15, vec[2]);
  EXPECT_EQ(30, vec[3]);
}

TEST(Task38, ConcatenateNumbersAsStrings) {
  std::vector<uint> vec{1, 2, 10, 56, 42};
  EXPECT_EQ("12105642", ConcatenateNumbersAsStrings(vec));
}

TASK(38) {
  mpz_class max_number;

  for (int i = 1; i < 10*1000; ++i) {
    std::string concatenated_product;
    std::vector<uint> numbers_1_to_n{1};
    for (int j = 2; concatenated_product.size() <= 9; ++j) {
      numbers_1_to_n.push_back(j);
      std::vector<uint> products = MultiplyEachElement(numbers_1_to_n, i);
      concatenated_product = ConcatenateNumbersAsStrings(products);

      if (Is1To9Pandigital(mpz_class(concatenated_product))) {
        max_number = std::max(max_number, mpz_class(concatenated_product));
      }
    }
  }

  SetResult(max_number.get_str());
}
