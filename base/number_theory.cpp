#include "base/number_theory.h"

bool IsPrime(int num) { return IsPrime(mpz_class(num)); }

bool IsPrime(const mpz_class &num) {
  return mpz_probab_prime_p(num.get_mpz_t(), 15) != 0;
}

std::vector<int> Sieve(int upper_limit) {
  std::vector<bool> bitmap(upper_limit, true);
  std::vector<int> result;

  for (int i = 2; i < upper_limit / 2; ++i) {
    if (bitmap[i]) {
      result.push_back(i);
      for (int64_t j = (int64_t)i * i; j < upper_limit; j += i) {
        bitmap[j] = false;
      }
    }
  }

  for (int i = upper_limit / 2; i < upper_limit; ++i) {
    if (bitmap[i]) {
      result.push_back(i);
    }
  }

  return result;
}

std::map<mpz_class, uint> Factorize(const mpz_class &number) {
  mpz_class num = number;
  std::map<mpz_class, uint> factorization;

  mpz_class prime = 2;
  while (num != 1) {
    uint deg = 0;
    if (mpz_divisible_p(num.get_mpz_t(), prime.get_mpz_t()) != 0) {
      deg = mpz_remove(num.get_mpz_t(), num.get_mpz_t(), prime.get_mpz_t());
    }

    if (deg > 0) {
      factorization[prime] = deg;
    }

    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
  }

  return factorization;
}

int NumberOfPrimeDivisors(const mpz_class &number) {
  mpz_class num = number;
  int result = 0;

  mpz_class prime = 2;
  while (num != 1) {
    if (mpz_divisible_p(num.get_mpz_t(), prime.get_mpz_t()) != 0) {
      result++;
      mpz_remove(num.get_mpz_t(), num.get_mpz_t(), prime.get_mpz_t());
    }

    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
  }

  return result;
}

mpz_class SumOfAllDivisors(const mpz_class &number) {
  auto list_of_divisors = Factorize(number);

  mpz_class res = 1;

  for (auto it : list_of_divisors) {
    auto &prime = it.first;
    uint deg = it.second;

    mpz_class tmp;
    mpz_pow_ui(tmp.get_mpz_t(), prime.get_mpz_t(), deg + 1);

    res *= (tmp - 1) / (prime - 1);
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
    mpq_class tmp = fraction * (ten_to_the_power_of_k - 1);
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

mpz_class NthTriangleNumber(int n) {
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
  return doubled_num == sqrt * (sqrt + 1);
}

mpz_class NthSquareNumber(int n) {
  mpz_class result{n};

  result *= n;

  return result;
}

bool IsSquareNumber(const mpz_class &num) {
  // mpz_perfect_square_p returns 0 if the number is definitely not a square
  // and non-zero if it's probably a square so we must check for that later too.
  if (mpz_perfect_square_p(num.get_mpz_t()) == 0) {
    return false;
  }

  mpz_class square_root = sqrt(num);

  return square_root * square_root == num;
}

mpz_class NthPentagonalNumber(int n) {
  mpz_class result{n};

  result *= 3;  // result == 3n
  result -= 1;  // result == 3n - 1
  result *= n;  // result == n(3n - 1)

  // We know that n*(3n - 1) is divisible by 2 so mpz_divexact_ui(...) is
  // the most suitable function in this case.
  mpz_divexact_ui(result.get_mpz_t(), result.get_mpz_t(), 2);

  return result;
}

bool IsPentagonalNumber(const mpz_class &num) {
  // Since expressions x = n*(3n - 2)/2 and n = (sqrt(24x + 1) + 1)/6 are
  // equivalent it suffices to check 24x + 1 is a perfect square and
  // sqrt(24x + 1) has residue 5 modulo 6.
  mpz_class n_times_24_plus_1{num * 24 + 1};

  if (IsSquareNumber(n_times_24_plus_1) && sqrt(n_times_24_plus_1) % 6 == 5) {
    return true;
  }

  return false;
}

mpz_class NthHexagonalNumber(int n) {
  mpz_class result{n};

  result *= 2;  // result == 2n
  result -= 1;  // result == 2n - 1
  result *= n;  // result == n(2n - 1)

  return result;
}

bool IsHexagonalNumber(const mpz_class &num) {
  // Since expressions x = n*(2n - 1)/2 and n = (sqrt(8x + 1) + 1)/4 are
  // equivalent it suffices to check 8x + 1 is a perfect square and
  // sqrt(8x + 1) has residue 3 modulo 4.
  mpz_class n_times_8_plus_1{num * 8 + 1};

  if (IsSquareNumber(n_times_8_plus_1) && sqrt(n_times_8_plus_1) % 4 == 3) {
    return true;
  }

  return false;
}

mpz_class NthHeptagonalNumber(int n) {
  mpz_class result{n};

  result *= 5;  // result == 5n
  result -= 3;  // result == 5n - 3
  result *= n;  // result == n(5n - 3)

  // We know that n*(5n - 3) is divisible by 2 so mpz_divexact_ui(...) is
  // the most suitable function in this case.
  mpz_divexact_ui(result.get_mpz_t(), result.get_mpz_t(), 2);

  return result;
}

bool IsHeptagonalNumber(const mpz_class &num) {
  // Since expressions x = n*(2n - 1)/2 and n = (sqrt(40x + 9) + 3)/10 are
  // equivalent it suffices to check 40x + 9 is a perfect square and
  // sqrt(40x + 9) has residue 7 modulo 10.
  mpz_class n_times_40_plus_9{num * 40 + 9};

  if (IsSquareNumber(n_times_40_plus_9) && sqrt(n_times_40_plus_9) % 10 == 7) {
    return true;
  }

  return false;
}

mpz_class NthOctagonalNumber(int n) {
  mpz_class result{n};

  result *= 3;  // result == 3n
  result -= 2;  // result == 3n - 2
  result *= n;  // result == n(3n - 2)

  return result;
}

bool IsOctagonalNumber(const mpz_class &num) {
  // Since expressions x = n*(3n - 2) and n = (sqrt(3x + 1) + 1)/3 are
  // equivalent it suffices to check 3x + 1 is a perfect square and
  // sqrt(3x + 1) has residue 2 modulo 3.
  mpz_class n_times_3_plus_1{num * 3 + 1};

  if (IsSquareNumber(n_times_3_plus_1) && sqrt(n_times_3_plus_1) % 3 == 2) {
    return true;
  }

  return false;
}
