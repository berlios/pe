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

mpz_class NthTriangleNumber(uint n) {
  mpz_class result{n};

  result *= n;
  result += n;

  // We know that n*n + n is divisible by 2 so mpz_divexact_ui(...) is the most
  // suitable function in this case.
  mpz_divexact_ui(result.get_mpz_t(), result.get_mpz_t(), 2);

  return result;
}

bool IsTriangleNumber(const mpz_class &num) {
  mpz_class sqrt, doubled_num{num * 2};
  mpz_sqrt(sqrt.get_mpz_t(), doubled_num.get_mpz_t());
  return doubled_num == sqrt*(sqrt + 1);
}

mpz_class NthPentagonalNumber(uint n) {
  mpz_class result{n};

  result *= 3;  // result == 3n
  result -= 1;  // result == 3n - 1
  result *= n;  // result == n(3n - 1)

  // We know that n*(3n - 1) is divisible by 2 so mpz_divexact_ui(...) is the most
  // suitable function in this case.
  mpz_divexact_ui(result.get_mpz_t(), result.get_mpz_t(), 2);

  return result;
}

bool IsPentagonalNumber(const mpz_class &num) {
  // Since expressions x = n*(3n - 2)/2 and n = (sqrt(24x + 1) + 1)/6 are
  // equivalent it suffices to check 24x + 1 is a perfect square and
  // sqrt(24x + 1) has residue 5 modulo 6.
  mpz_class n_times_24_plus_1{num*24 + 1};

  // mpz_perfect_square_p returns 0 if the number is definitely not a square
  // and non-zero if it's probably a square so we must check for that later too.
  if (mpz_perfect_square_p(n_times_24_plus_1.get_mpz_t()) == 0) {
    return false;
  }

  mpz_class sqrt;
  mpz_sqrt(sqrt.get_mpz_t(), n_times_24_plus_1.get_mpz_t());

  if (sqrt*sqrt == n_times_24_plus_1 && sqrt % 6 == 5) {
    return true;
  } else {
    return false;
  }
}
