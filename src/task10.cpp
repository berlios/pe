#include <gmpxx.h>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;

string SumOfPrimesBelow(int n) {
  mpz_class prime = 2, sum = 0;
  while (prime < n) {
    sum += prime;
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
  }

  return sum.get_str();
}

TEST(Task10, SumOfPrimesBelow10) {
  EXPECT_EQ("17", SumOfPrimesBelow(10));
}

TASK(10) {
  SetResult(SumOfPrimesBelow(2*1000*1000));
}
