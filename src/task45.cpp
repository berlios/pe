#include <gmpxx.h>

#include "base/number_theory.h"
#include "base/task.h"

TASK(45) {
  // Any hexagonal number is also an odd-indexed triangle number so it suffices
  // to check only triangle numbers with indexes 1, 3, 5, etc if they are
  // pentagonal.
  uint triangle_index = 287;

  while (true) {
    mpz_class num = NthTriangleNumber(triangle_index);

    if (IsPentagonalNumber(num)) {
      return num;
    }

    triangle_index += 2;
  }
}
