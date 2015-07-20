#include <algorithm>
#include <vector>

#include "base/digit_manipulation.h"
#include "base/number_theory.h"
#include "base/task.h"

TASK(49) {
  auto prime_list = Sieve(10*1000);
  auto new_end = std::remove_if(prime_list.begin(), prime_list.end(),
                                [](int n) { return n < 1000; });
  prime_list.erase(new_end, prime_list.end());

  std::string result;
  for (int i = 0; i < prime_list.size(); ++i) {
    for (int j = i + 2; j < prime_list.size(); ++j) {
      int lowest_prime = prime_list[i];
      int highest_prime = prime_list[j];
      int mid_prime = (lowest_prime + highest_prime) / 2;
      if (!std::binary_search(prime_list.begin(), prime_list.end(),
                              mid_prime)) {
        continue;
      }

      if (GetDigitSet(lowest_prime) == GetDigitSet(mid_prime) &&
          GetDigitSet(lowest_prime) == GetDigitSet(highest_prime)) {
        if (lowest_prime == 1487 && mid_prime == 4817 &&
            highest_prime == 8147) {
          continue;
        } else {
          result += std::to_string(lowest_prime);
          result += std::to_string(mid_prime);
          result += std::to_string(highest_prime);
        }
      }
    }
  }

  return result;
}
