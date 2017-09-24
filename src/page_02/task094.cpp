#include "base/number_theory.h"
#include "base/task.h"

TASK(94) {
  int perimeter_sum = 0;
  // No solutions for even i exist.
  for (int64_t i = 3; i <= (1000 * 1000 * 1000 - 1) / 3; i += 2) {
    int64_t under_root = (3 * i + 1) * (i - 1);
    if (IsSquareNumber(under_root)) {
      perimeter_sum += 3 * i + 1;
    }

    under_root = (3 * i - 1) * (i + 1);
    if (IsSquareNumber(under_root)) {
      perimeter_sum += 3 * i - 1;
    }
  }
  return perimeter_sum;
}
