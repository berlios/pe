#include "base/task.h"

// If the number k has n digits then 10^(n - 1) <= k.
// On the other hand, k <= n*9^5.
// So 10^(n - 1) <= n*9^5, which gives us n <= 6.

TASK(30) {
  int res = 0;
  for (int i = 10; i < 1000*1000; ++i) {
    int n = i;
    int sum = 0;
    while (n > 0) {
      int last_digit = n % 10;
      sum += last_digit*last_digit*last_digit*last_digit*last_digit;
      n = n / 10;
    }
    if (sum == i) {
      res += i;
    }
  }

  SetResult(ToString(res));
}
