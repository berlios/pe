#include <algorithm>
#include <gmpxx.h>
#include <vector>

#include "base/task.h"

TASK(46) {
  for (mpz_class i = 9;; i += 2) {
    if (mpz_probab_prime_p(i.get_mpz_t(), 15) != 0) {
      continue;
    }

    bool found = false;
    for (mpz_class prime{3}; prime <= i - 2; mpz_nextprime(prime.get_mpz_t(),
                                                           prime.get_mpz_t())) {
      mpz_class square{(i - prime)/2};
      if (mpz_perfect_square_p(prime.get_mpz_t()) != 0) {
        continue;
      }

      mpz_class sqrt;
      mpz_sqrt(sqrt.get_mpz_t(), square.get_mpz_t());
      if (sqrt*sqrt == square) {
        found = true;
        break;
      }
    }

    if (!found) {
      return i;
    }
  }
}
