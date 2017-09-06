#include <algorithm>
#include <string>

#include "base/common.h"
#include "base/digit_manipulation.h"
#include "base/task.h"
#include "gtest/gtest.h"

using std::abs;
using std::min;
using std::string;

// Finds largest integer palindrom that can be represented as x*y
// with x and y both less than this function's only argument.
string LargestPalindrome(int cap) {
  int largest_palindrome = 0;
  // i denotes x+y during every iteration
  for (int i = 2*(cap - 1); (i >= 0) && (largest_palindrome == 0); --i) {
    // I'm pretty positive that both arguments of min() will be positive.
    int max_j = min(2*(cap - 1) - i, i);
    for (int j = -max_j; j <= max_j; j += 2) {
      // Here i and j should both have the same parity.
      int x = (i + j)/2;
      int y = (i - j)/2;

      if (IsPalindrome(x*y) && largest_palindrome < x*y) {
        largest_palindrome = x*y;
      }
    }
  }

  return ToString(largest_palindrome);
}

TEST(Task4, LargestPalindrome) {
  EXPECT_EQ("9009", LargestPalindrome(100));
}

TASK(4) {
  return LargestPalindrome(1000);
}
