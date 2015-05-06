#include <algorithm>
#include <gmpxx.h>
#include <set>

#include "base/task.h"

TASK(29) {
  std::set<mpz_class> sequence;

  for (uint a = 2; a <= 100; ++a) {
    for (uint b = 2; b <= 100; ++b) {
      mpz_class n = a;
      mpz_pow_ui(n.get_mpz_t(), n.get_mpz_t(), b);
      sequence.insert(n);
    }
  }

  SetResult(ToString(sequence.size()));
}
