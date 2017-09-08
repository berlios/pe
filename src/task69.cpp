#include <gmpxx.h>

#include "base/number_theory.h"
#include "base/task.h"

TASK(69) {
  auto primes = Sieve(1000*1000);
  int64_t n = 1;
  for (int i : primes) {
    if (n * i < 1000*1000) {
      n *= i;
    }
  }

  return n;
}
