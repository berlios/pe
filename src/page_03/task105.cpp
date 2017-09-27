#include <vector>

#include "base/common.h"
#include "base/task.h"

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
}

TASK(105) {
  auto lines =
      Split(ReadFileIntoString("data/105_sets.txt"), '\n', SkipEmpty());

  int sum = 0;
  for (const std::string& line : lines) {
    auto numbers = Split(line, ',');
    std::vector<int> number_set;
    std::transform(numbers.begin(), numbers.end(),
                   std::back_inserter(number_set),
                   [](const std::string& s) { return stoi(s); });
    if (CheckRules(number_set)) {
      sum += std::accumulate(number_set.begin(), number_set.end(), 0);
    }
  }
  return sum;
}
