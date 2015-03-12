#include <gmpxx.h>

#include "base/task.h"
#include "gtest/gtest.h"

TASK(25) {
  mpz_class num;

  for (int i = 1;; ++i) {
    mpz_fib_ui(num.get_mpz_t(), i);

    if (num.get_str().size() >= 1000) {
      SetResult(ToString(i));
      return;
    }
  }
}
