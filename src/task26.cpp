#include <algorithm>
#include <gmpxx.h>

#include "base/number_theory.h"
#include "base/task.h"

TASK(26) {
  uint longest_cycle_length = 0;
  int result;
  for (int i = 2; i < 1000; ++i) {
    uint current_cycle_length = LengthOfRepeatingCycle(mpq_class(1, i));
    if (longest_cycle_length < current_cycle_length) {
      longest_cycle_length = current_cycle_length;
      result = i;
    }
  }

  SetResult(ToString(result));
}
