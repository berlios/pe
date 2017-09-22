#include <gmpxx.h>
#include <string>
#include <vector>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;
using std::vector;

int NumberOfDivisors(const mpz_class& n) {
  vector<mpz_class> divisors;
  vector<int> powers;
  mpz_class number = n;

  for (mpz_class prime = 2; number != 1;
       mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t())) {
    int power = mpz_remove(number.get_mpz_t(), number.get_mpz_t(),
                           prime.get_mpz_t());
    if (power > 0) {
      divisors.push_back(prime);
      powers.push_back(power);
    }
  }

  int result = 1;
  for (size_t i = 0; i < powers.size(); ++i) {
    result = result*(powers[i] + 1);
  }

  return result;
}

TEST(Task12, NumberOfDivisors) {
  EXPECT_EQ(1, NumberOfDivisors(1));
  EXPECT_EQ(2, NumberOfDivisors(3));
  EXPECT_EQ(4, NumberOfDivisors(6));
  EXPECT_EQ(4, NumberOfDivisors(10));
  EXPECT_EQ(4, NumberOfDivisors(15));
  EXPECT_EQ(4, NumberOfDivisors(21));
  EXPECT_EQ(6, NumberOfDivisors(28));
}

TASK(12) {
  mpz_class result;
  int prev = NumberOfDivisors(1);

  for (mpz_class i = 2; ; ++i) {
    mpz_class corrected_i = i;
    if (i%2 == 0) {
      corrected_i = i/2;
    }

    int current = NumberOfDivisors(corrected_i);
    if (current*prev > 500) {
      result = i*(i-1)/2;
      break;
    }

    prev = current;
  }

  return result.get_str();
}
