#include <gmpxx.h>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;

// Both ends inclusive.
string LCDOfRangeFrom1To(int n) {
  mpz_class lcm = 1;
  for (int i = 1; i <= n; ++i) {
    mpz_lcm_ui(lcm.get_mpz_t(), lcm.get_mpz_t(), static_cast<unsigned long>(i));
  }

  return lcm.get_str();
}

TEST(Task5, LCDOfRangeFrom1To10) {
  EXPECT_EQ("2520", LCDOfRangeFrom1To(10));
}

TASK(5) {
  return LCDOfRangeFrom1To(20);
}
