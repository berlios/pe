#include <gmpxx.h>

#include "base/digit_manipulation.h"
#include "base/task.h"
#include "gtest/gtest.h"

bool IsLychrel(const mpz_class& n) {
  mpz_class candidate = n;
  for (int i = 0; i < 50; ++i) {
    candidate = candidate + Reverse(candidate);
    if (IsPalindrome(candidate)) {
      return false;
    }
  }

  return true;
}

TEST(Task55, IsLychrel) {
  EXPECT_FALSE(IsLychrel(47));
  EXPECT_FALSE(IsLychrel(349));

  EXPECT_TRUE(IsLychrel(196));
  EXPECT_TRUE(IsLychrel(4994));

  // It takes more than 50 iteration to arrive at a palindrome for 10677.
  EXPECT_TRUE(IsLychrel(10677));
}

TASK(55) {
  int counter = 0;
  for (int i = 1; i < 10000; ++i) {
    if (IsLychrel(i)) {
      ++counter;
    }
  }

  return counter;
}
