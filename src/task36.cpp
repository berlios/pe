#include <algorithm>
#include <gmpxx.h>
#include <string>

#include "base/digit_manipulation.h"
#include "base/task.h"

TASK(36) {
  uint sum = 0;

  for (uint i = 1; i < 1000*1000; ++i) {
    if (i == ReverseInBase(i, 10) && i == ReverseInBase(i, 2)) {
      sum += i;
    }
  }

  SetResult(ToString(sum));
}
