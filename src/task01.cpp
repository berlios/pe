#include <sstream>

#include "base/task.h"
#include "gtest/gtest.h"

static int main_func(int cap) {
  int sum = 0;
  for (int i = 1; i < cap; ++i) {
    if (i%3 == 0  || i%5 == 0)
      sum += i;
  }

  return sum;
}

TEST(Task1, CapEquals10) {
  EXPECT_EQ(23, main_func(10));
}

TASK(1) {
  return main_func(1000);
}
