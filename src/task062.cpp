#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

#include "base/task.h"
#include "gtest/gtest.h"

int64_t FindSmallestCubeWithNPermutations(int n) {
  std::unordered_map<std::string, std::vector<int64_t>> m;
  for (int64_t i = 1; i <= 2*1024*1024; ++i) {
    std::string str = std::to_string(i*i*i);
    std::sort(str.begin(), str.end());
    auto& numbers = m[str];
    numbers.push_back(i*i*i);
    if (numbers.size() == static_cast<size_t>(n)) {
      return numbers[0];
    }
  }
  return -1;
}

TEST(Task62, FindSmallestCubeWithNPermutations) {
  EXPECT_EQ(41063625, FindSmallestCubeWithNPermutations(3));
}

TASK(62) {
  return FindSmallestCubeWithNPermutations(5);
}
