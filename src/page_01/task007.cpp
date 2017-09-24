#include <gmpxx.h>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;

string NthPrime(int n) {
  mpz_class prime = 1;
  for (int i = 0; i < n; ++i) {
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
  }

  return prime.get_str();
}

TEST(Task7, PrimeNumber6) {
  EXPECT_EQ("13", NthPrime(6));
}

TASK(7) {
  return NthPrime(10001);
}
