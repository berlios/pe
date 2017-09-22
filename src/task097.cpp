#include <gmpxx.h>

#include "base/task.h"

TASK(97) {
  constexpr int64_t mod = static_cast<int64_t>(10) * 1000 * 1000 * 1000;

  mpz_class n = 2;
  mpz_powm_ui(n.get_mpz_t(), n.get_mpz_t(), 7830457,
              mpz_class(mod).get_mpz_t());
  n = n * 28433 + 1;
  return mpz_class(n % mod);
}
