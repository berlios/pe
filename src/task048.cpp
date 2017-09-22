#include <gmpxx.h>

#include "base/task.h"

TASK(48) {
  mpz_class result = 0, mod = (uint64_t)10*1000*1000*1000;
  for (int i = 1; i <= 1000; ++i) {
    mpz_class i_to_the_power_i = i;
    mpz_powm_ui(i_to_the_power_i.get_mpz_t(), i_to_the_power_i.get_mpz_t(),
                i, mod.get_mpz_t());
    result += i_to_the_power_i;
  }

  mpz_mod(result.get_mpz_t(), result.get_mpz_t(), mod.get_mpz_t());
  return result;
}
