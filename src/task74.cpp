#include <algorithm>
#include <array>

#include "base/task.h"
#include "gtest/gtest.h"

int SumOfDigitFactorials(int n) {
  static const std::array<int, 10> factorials = [] {
    std::array<int, 10> t;
    t[0] = 1;
    for (size_t i = 1; i < t.size(); ++i) {
      t[i] = t[i - 1] * i;
    }
    return t;
  }();

  int result = 0;
  while (n > 0) {
    result += factorials[n % 10];
    n /= 10;
  }
  return result;
}

TEST(Task74, SumOfDigitFactorials) {
  EXPECT_EQ(145, SumOfDigitFactorials(145));
  EXPECT_EQ(363601, SumOfDigitFactorials(169));
}

TASK(74) {
  int counter = 0;
  for (int i = 1; i < 1000 * 1000; ++i) {
    std::vector<int> sequence;
    sequence.push_back(i);
    while (true) {
      int next = SumOfDigitFactorials(sequence.back());
      if (std::find(sequence.begin(), sequence.end(), next) != sequence.end()) {
        break;
      }
      sequence.push_back(next);
    }

    if (sequence.size() == 60) {
      counter++;
    }
  }
  return counter;
}
