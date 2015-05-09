#include <set>

#include "base/digit_manipulation.h"
#include "base/task.h"

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
