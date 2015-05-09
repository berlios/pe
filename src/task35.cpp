#include <gmpxx.h>

#include "base/digit_manipulation.h"
#include "base/task.h"

TASK(35) {
  mpz_class prime = 2;
  int circular_primes_count = 0;
  while (prime < 1000*1000) {
    mpz_class copy = prime;
    bool is_circular = true;
    for (int i = 0; i < mpz_sizeinbase(prime.get_mpz_t(), 10); ++i) {
      if (mpz_probab_prime_p(copy.get_mpz_t(), 20) == 0) {
        is_circular = false;
        break;
      }
      copy = PlaceLastDigitInFront(copy);
    }

    if (is_circular) {
      circular_primes_count++;
    }

    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
  }

  SetResult(ToString(circular_primes_count));
}
