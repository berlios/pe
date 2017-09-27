#include <algorithm>
#include <limits>
#include <vector>

#include "base/task.h"
#include "gtest/gtest.h"

namespace {
bool CheckRules(const std::vector<int>& number_set) {
  for (int i = 1; i <= static_cast<int>(number_set.size() / 2); ++i) {
    for (int j = i; j <= static_cast<int>(number_set.size()) - i; ++j) {
      std::vector<int> selection(number_set.size());
      for (int k = 0; k < static_cast<int>(selection.size()); ++k) {
        if (k >= static_cast<int>(selection.size()) - j) {
          selection[k] = 2;
        } else if (k >= static_cast<int>(selection.size()) - i - j) {
          selection[k] = 1;
        }
      }

      do {
        int sum_1 = 0;
        int sum_2 = 0;
        for (int k = 0; k < static_cast<int>(number_set.size()); ++k) {
          if (selection[k] == 1) {
            sum_1 += number_set[k];
          }
          if (selection[k] == 2) {
            sum_2 += number_set[k];
          }
        }
        if (i != j && sum_1 >= sum_2) {
          return false;
        }
        if (i == j && sum_1 == sum_2) {
          return false;
        }
      } while (std::next_permutation(selection.begin(), selection.end()));
    }
  }

  return true;
}

bool NextFluctuation(int range, std::vector<int>* fluctuations) {
  for (auto it = fluctuations->rbegin(); it != fluctuations->rend(); ++it) {
    if (*it == range) {
      *it = -range;
    } else {
      *it += 1;
      return true;
    }
  }
  return false;
}
}

TEST(Task103, CheckRules) {
  std::vector<int> number_set{6, 9, 11, 12, 13};
  EXPECT_TRUE(CheckRules(number_set));

  number_set = {20, 31, 38, 39, 40, 42, 45};
  EXPECT_TRUE(CheckRules(number_set));
}

TASK(103) {
  std::vector<int> number_set{11, 18, 19, 20, 22, 25};
  int middle_element = number_set[number_set.size() / 2];
  std::vector<int> starting_set{middle_element};
  std::transform(number_set.begin(), number_set.end(),
                 std::back_inserter(starting_set),
                 [middle_element](int n) { return n + middle_element; });

  std::vector<int> fluctuations(starting_set.size(), -3);

  int min_sum = std::numeric_limits<int>::max();
  std::string result;

  do {
    std::vector<int> approximation = starting_set;
    for (size_t i = 0; i < approximation.size(); ++i) {
      approximation[i] += fluctuations[i];
    }

    std::sort(approximation.begin(), approximation.end());

    if (CheckRules(approximation)) {
      int current_sum =
          std::accumulate(approximation.begin(), approximation.end(), 0);
      if (current_sum < min_sum) {
        min_sum = current_sum;
        result.clear();
        for (int n : approximation) {
          result += std::to_string(n);
        }
      }
    }

  } while (NextFluctuation(3, &fluctuations));

  return result;
}
