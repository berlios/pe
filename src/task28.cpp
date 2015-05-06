#include "base/task.h"

// If the square is (2n + 1)*(2n + 1) then
//   - the upper right number is (2n + 1)^2
//   - the upper left number is (2n + 1)^2 - 2n
//   - the lower left number is (2n + 1)^2 - 4n
//   - the lower right number is (2n + 1)^2 - 6n
// Total: 4*(2n + 1)^2 - 12n

TASK(28) {
  int sum = 1;
  for (int i = 1; i <= 500; ++i) {
    sum += 4*(2*i + 1)*(2*i + 1) - 12*i;
  }

  SetResult(ToString(sum));
}
