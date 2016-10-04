#include <gmpxx.h>

#include "base/task.h"

TASK(53) {
  int result = 0;
  for (int n = 1; n <= 100; ++n) {
    for (int r = 0; r <= n; ++r) {
      mpz_class b;
      mpz_bin_uiui(b.get_mpz_t(), n, r);
      if (b > 1000*1000) {
        result++;
      }
    }
  }

  return result;
}
