#include <algorithm>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

bool IsSubStringDivisible(int64_t num) {
  std::string num_str = std::to_string(num);

  if (num_str.size() != 10) {
    return false;
  }

  return (std::stoi(num_str.substr(1, 3)) %  2) == 0 &&
         (std::stoi(num_str.substr(2, 3)) %  3) == 0 &&
         (std::stoi(num_str.substr(3, 3)) %  5) == 0 &&
         (std::stoi(num_str.substr(4, 3)) %  7) == 0 &&
         (std::stoi(num_str.substr(5, 3)) % 11) == 0 &&
         (std::stoi(num_str.substr(6, 3)) % 13) == 0 &&
         (std::stoi(num_str.substr(7, 3)) % 17) == 0;
}

TEST(Task43, SubStringDivisible) {
  // Just in case.
  EXPECT_EQ(83, std::stoll("083"));
  EXPECT_TRUE(IsSubStringDivisible(1406357289));
}

TASK(43) {
  int64_t sum = 0;
  for (std::string num_str = "0123456789";
       std::next_permutation(num_str.begin(), num_str.end());) {
    if (IsSubStringDivisible(std::stoll(num_str))) {
      sum += std::stoll(num_str);
    }
  }

  return sum;
}
