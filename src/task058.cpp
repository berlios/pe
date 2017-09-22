#include "base/task.h"

// If the square is (2n + 1)*(2n + 1) then
//   - the lower right number is (2n + 1)^2
//   - the lower left number is (2n + 1)^2 - 2n
//   - the upper left number is (2n + 1)^2 - 4n
//   - the upper right number is (2n + 1)^2 - 6n

TASK(58) {
  int side = 3;

  // Primes on the diagonals are 3, 5 and 7.
  int prime_count = 3;
  int total_count = 5;

  while (prime_count * 10 >= total_count) {
    total_count += 4;
    side += 2;
    int n = side / 2;

    mpz_class candidate = side * side - 2 * n;
    if (mpz_probab_prime_p(candidate.get_mpz_t(), 15) != 0) {
      ++prime_count;
    }

    candidate -= 2 * n;
    if (mpz_probab_prime_p(candidate.get_mpz_t(), 15) != 0) {
      ++prime_count;
    }

    candidate -= 2 * n;
    if (mpz_probab_prime_p(candidate.get_mpz_t(), 15) != 0) {
      ++prime_count;
    }

  }

  return side;
}
