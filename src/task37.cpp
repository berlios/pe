#include <gmpxx.h>
#include <vector>

#include "base/digit_manipulation.h"
#include "base/task.h"

bool TruncatablePrime(const mpz_class &num) {
  mpz_class copy = num;
  while (copy != 0) {
    if (mpz_probab_prime_p(copy.get_mpz_t(), 15) == 0) {
      return false;
    }
    copy = DeleteFirstDigit(copy);
  }

  copy = num;
  while (copy != 0) {
    if (mpz_probab_prime_p(copy.get_mpz_t(), 15) == 0) {
      return false;
    }
    copy = DeleteLastDigit(copy);
  }

  return true;
}

TASK(37) {
  mpz_class prime = 11;
  std::vector<mpz_class> truncatable_primes;

  while (truncatable_primes.size() < 11) {
    if (TruncatablePrime(prime)) {
      truncatable_primes.push_back(prime);
    }
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
  }

  mpz_class result;
  for (auto &num : truncatable_primes) {
    result += num;
  }

  SetResult(result.get_str());
}
