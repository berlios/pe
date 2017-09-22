#include <gmpxx.h>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;

// Computes (1 + 2 + ... + n)^2 - (1^2 + 2^2 + ... + n^2)
string SquareDifference(int n) {
  mpz_class m = n;
  mpz_class a = m*m*(m + 1)*(m + 1)/4;
  mpz_class b = m*(m + 1)*(2*m + 1)/6;
  return static_cast<mpz_class>(a - b).get_str();
}

TEST(Task6, SquareDifferenceFor10) {
  EXPECT_EQ("2640", SquareDifference(10));
}

TASK(6) {
  return SquareDifference(100);
}
