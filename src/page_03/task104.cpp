#include <gmpxx.h>

#include "base/digit_manipulation.h"
#include "base/task.h"
#include "gtest/gtest.h"

namespace {
bool IsString1To9Pandigital(const std::string& s) {
  if (s.size() != 9) {
    return false;
  }

  std::string copy_of_s = s;
  std::sort(copy_of_s.begin(), copy_of_s.end());

  return copy_of_s == "123456789";
}
}

TEST(Task104, IsString1To9Pandigital) {
  EXPECT_TRUE(IsString1To9Pandigital("123456789"));
  EXPECT_TRUE(IsString1To9Pandigital("987654321"));
}

TASK(104) {
  int a = 1;
  int b = 1;
  constexpr int mod = 1000*1000*1000;
  int k = 2;

  while (true) {
    int c = (a + b) % mod;
    a = b;
    b = c;
    k++;

    if (!Is1To9Pandigital(b)) {
      continue;
    }

    mpz_class fib;
    mpz_fib_ui(fib.get_mpz_t(), k);
    std::string s = fib.get_str();

    if (IsString1To9Pandigital(s.substr(0, 9))) {
      break;
    }
  }

  return k;
}

