#include <algorithm>
#include <array>
#include <string>

#include "base/task.h"

// If no valid magic 5-ring can be reconstructed then this function returns
// an empty string.
std::string ReconstructAndScoreRingFromInnerCircle(
    const std::array<int, 5>& inner_circle, int sum_of_each_row_of_three) {
  std::array<int, 5> outer_circle;
  for (int i = 0; i < 5; ++i) {
    outer_circle[i] =
        sum_of_each_row_of_three - inner_circle[i] - inner_circle[(i + 1) % 5];
    if (outer_circle[i] <= 0) {
      return "";
    }
  }

  for (int i = 1; i <= 10; ++i) {
    if (std::find(inner_circle.begin(), inner_circle.end(), i) !=
        inner_circle.end()) {
      continue;
    }
    if (std::find(outer_circle.begin(), outer_circle.end(), i) !=
        outer_circle.end()) {
      continue;
    }

    return "";
  }

  auto it = std::min_element(outer_circle.begin(), outer_circle.end());
  int start = std::distance(outer_circle.begin(), it);
  std::string result;
  for (int i = 0; i < 5; ++i) {
    result += std::to_string(outer_circle[(start + i) % 5]);
    result += std::to_string(inner_circle[(start + i) % 5]);
    result += std::to_string(inner_circle[(start + i + 1) % 5]);
  }

  return result;
}

TASK(68) {
  std::array<int, 10> a = {{-1, -1, -1, -1, -1, 0, 1, 2, 3, 4}};

  std::string max_string(16, '0');
  do {
    std::array<int, 5> inner_circle;
    for (size_t i = 0; i < a.size(); ++i) {
      if (a[i] >= 0) {
        inner_circle[a[i]] = i + 1;
      }
    }

    std::array<int, 6> possible_sums = {{14, 15, 16, 17, 18, 19}};

    for (int sum : possible_sums) {
      std::string s = ReconstructAndScoreRingFromInnerCircle(inner_circle, sum);
      if (s.size() != 16) {
        continue;
      }
      max_string = std::max(max_string, s);
    }
  } while (std::next_permutation(a.begin(), a.end()));

  return max_string;
}
