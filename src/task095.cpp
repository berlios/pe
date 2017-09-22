#include <algorithm>
#include <vector>

#include "base/task.h"

TASK(95) {
  std::vector<int> sum_of_proper_divisors(1000 * 1000 + 1, 1);
  for (size_t i = 2; i < sum_of_proper_divisors.size() / 2; ++i) {
    for (size_t j = 2; j < sum_of_proper_divisors.size() / i; ++j) {
      sum_of_proper_divisors[j * i] += i;
    }
  }

  int result = -1;
  size_t longest_chain_length = 0;

  for (size_t i = 2; i < sum_of_proper_divisors.size(); ++i) {
    std::vector<int> chain{static_cast<int>(i)};
    while (true) {
      int next_number = sum_of_proper_divisors[chain.back()];
      if (next_number > 1000*1000) {
        break;
      }

      auto it = std::find(chain.rbegin(), chain.rend(), next_number);
      if (it == chain.rend()) {
        chain.push_back(next_number);
        continue;
      }

      if (std::next(it) == chain.rend()) {
        if (longest_chain_length < chain.size()) {
          longest_chain_length = chain.size();
          result = chain[0];
        }
      }

      break;
    }
  }

  return result;
}
