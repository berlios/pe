#include <gmpxx.h>
#include <map>

#include "base/task.h"
#include "gtest/gtest.h"

std::map<mpz_class, uint> Factorize(const mpz_class &number) {
  mpz_class num = number;
  std::map<mpz_class, uint> factorization;

  mpz_class i = 2;
  while (num != 1) {
    uint deg = 0;
    mpz_class r = num % i;
    while (r == 0) {
      deg++;
      num = num / i;
      r = num % i;
    }

    if (deg > 0) {
      factorization[i] = deg;
    }

    mpz_nextprime(i.get_mpz_t(), i.get_mpz_t());
  }

  return factorization;
}

mpz_class SumOfAllDivisors(const mpz_class &number) {
  auto list_of_divisors = Factorize(number);

  mpz_class res = 1;

  for (auto it : list_of_divisors) {
    auto &prime = it.first;
    uint deg = it.second;

    mpz_class tmp;
    mpz_pow_ui(tmp.get_mpz_t(), prime.get_mpz_t(), deg + 1);

    res *= (tmp - 1)/(prime - 1);
  }

  return res;
}

mpz_class SumOfProperDivisors(const mpz_class &number) {
  mpz_class total_sum = SumOfAllDivisors(number);
  return total_sum - number;
}

TEST(Task21, SumOfDivisors) {
  mpz_class a = 8;
  EXPECT_EQ(15, SumOfAllDivisors(a));
  EXPECT_EQ(7, SumOfProperDivisors(a));

  a = 24;
  EXPECT_EQ(60, SumOfAllDivisors(a));
  EXPECT_EQ(36, SumOfProperDivisors(a));

  a = 3;
  EXPECT_EQ(4, SumOfAllDivisors(a));
  EXPECT_EQ(1, SumOfProperDivisors(a));
}

TEST(Task21, Numbers220And284AreAmicable) {
  EXPECT_EQ(284, SumOfProperDivisors(220));
  EXPECT_EQ(220, SumOfProperDivisors(284));
}

TASK(21) {
  int sum = 0;

  for (int i = 2; i < 10000; ++i) {
    mpz_class pair = SumOfProperDivisors(i);
    if (pair < 10000 && i != pair && i == SumOfProperDivisors(pair)) {
      printf("%d\n", i);
      sum += i;
    }
  }

  SetResult(ToString(sum));
}
