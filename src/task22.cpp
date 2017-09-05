#include <algorithm>
#include <string>
#include <vector>

#include "base/common.h"
#include "base/task.h"
#include "gtest/gtest.h"

TEST(Task22, Colin) {
  std::vector<std::string> words{
#include "src/data/022_names.txt"
  };

  std::sort(words.begin(), words.end());
  EXPECT_EQ("COLIN", words[938 - 1]);
  EXPECT_EQ(53, AlphabeticalValue(words[938 - 1]));
}

TASK(22) {
  std::vector<std::string> words{
#include "src/data/022_names.txt"
  };

  std::sort(words.begin(), words.end());

  uint total_score = 0;
  for (size_t i = 0; i < words.size(); ++i) {
    total_score += AlphabeticalValue(words[i]) * (i + 1);
  }

  return total_score;
}
