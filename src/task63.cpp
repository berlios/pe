#include "base/task.h"

// The key observation here is that 10^n always has n+1 digits so if 9^n has
// fewer than n digits then there's no solutions for a particlar n.
// 9^n > 10^(n-1) <=> n < 21.854...
TASK(63) {
  int counter = 0;
  for (int n = 1; n <= 21; ++n) {
    for (int i = 9; i > 0; --i) {
      mpz_class num;
      mpz_ui_pow_ui(num.get_mpz_t(), i, n);
      if (num.get_str().size() < static_cast<size_t>(n)) {
        break;
      }

      counter++;
    }
  }

  return counter;
}
