#include "base/number_theory.h"

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

uint LengthOfRepeatingCycle(const mpq_class &fraction) {
  auto copy = fraction;
  copy.canonicalize();
  auto f = Factorize(copy.get_den());
  f.erase(2);
  f.erase(5);
  if (f.size() == 0) {
    return 0;
  }

  uint k = 1;
  mpz_class ten_to_the_power_of_k = 10;

  while (true) {
    mpq_class tmp = fraction*(ten_to_the_power_of_k - 1);
    tmp.canonicalize();

    auto denominator_factorization = Factorize(tmp.get_den());
    denominator_factorization.erase(2);
    denominator_factorization.erase(5);

    if (denominator_factorization.size() == 0) {
      return k;
    } else {
      k++;
      ten_to_the_power_of_k *= 10;
    }
  }
}

