#include <algorithm>

#include "base/number_theory.h"
#include "base/task.h"
#include "gtest/gtest.h"

int SumOfLongestPrimeSequenceAddingToAPrimeBelow(int upper_limit) {
  auto sieve = Sieve(upper_limit);

  std::vector<int64_t> consecutive_sums(sieve.size() + 1);
  consecutive_sums[0] = 0;
  for (size_t i = 0; i < sieve.size(); ++i) {
    consecutive_sums[i + 1] = consecutive_sums[i] + sieve[i];
  }

  auto is_prime = [&sieve](int p) {
    return std::binary_search(sieve.cbegin(), sieve.cend(), p);
  };

  size_t max_length = 0;
  int64_t result;
  for (size_t i = 0; i < sieve.size(); ++i) {
    for (size_t j = i; j < sieve.size(); ++j) {
      int64_t maybe_prime = consecutive_sums[j + 1] - consecutive_sums[i];
      size_t length = j - i + 1;

      if (maybe_prime >= upper_limit || length <= max_length) {
        continue;
      }

      if (is_prime(maybe_prime) && max_length < j - i + 1) {
        max_length = j - i + 1;
        result = maybe_prime;
      }
    }
  }

  return result;
}

TEST(Task50, SumOfLongestPrimeSequenceAddingToAPrimeBelow) {
  EXPECT_EQ(41, SumOfLongestPrimeSequenceAddingToAPrimeBelow(100));
  EXPECT_EQ(953, SumOfLongestPrimeSequenceAddingToAPrimeBelow(1000));
}

TASK(50) { return SumOfLongestPrimeSequenceAddingToAPrimeBelow(1000 * 1000); }
