#include <gmpxx.h>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;

string LargestPrimeFactor(const string &number) {
  mpz_class num(number), largest_prime(0);
  mpz_class root_of_num;
  mpz_sqrt(root_of_num.get_mpz_t(), num.get_mpz_t());

  for (mpz_class i = 2; mpz_cmp(i.get_mpz_t(), root_of_num.get_mpz_t()) < 0;
       mpz_nextprime(i.get_mpz_t(), i.get_mpz_t())) {
    if (mpz_divisible_p(num.get_mpz_t(), i.get_mpz_t())) {
      largest_prime = i;
    }
  }
  return largest_prime.get_str();
}

TEST(Task3, LargestPrimeFactorOf13195) {
  EXPECT_EQ("29", LargestPrimeFactor("13195"));
}

TASK(3) {
  SetResult(LargestPrimeFactor("600851475143"));
}
