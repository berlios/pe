#include <algorithm>
#include <string>

#include "base/common.h"
#include "base/task.h"
#include "gtest/gtest.h"

uint AlphabeticalValue(const std::string &word) {
  uint score = 0;
  for (size_t i = 0; i < word.size(); ++i) {
    score += word[i] - 'A' + 1;
  }

  return score;
}

TEST(Task22, Colin) {
  std::string contents;
  ReadFileIntoString("../src/22_names.txt", &contents);

  auto words = Split(contents, ',');

  for (auto &word : words) {
    word = word.substr(1, word.size() - 2);
  }

  std::sort(words.begin(), words.end());
  EXPECT_EQ("COLIN", words[938 - 1]);
  EXPECT_EQ(53, AlphabeticalValue(words[938 - 1]));
}

TASK(22) {
  std::string contents;
  ReadFileIntoString("../src/22_names.txt", &contents);

  auto words = Split(contents, ',');

  for (auto &word : words) {
    word = word.substr(1, word.size() - 2);
  }

  std::sort(words.begin(), words.end());

  uint total_score = 0;
  for (size_t i = 0; i < words.size(); ++i) {
    total_score += AlphabeticalValue(words[i]) * (i + 1);
  }

  SetResult(ToString(total_score));
}
