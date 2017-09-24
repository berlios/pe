#include "base/number_theory.h"
#include "base/task.h"

TASK(86) {
  std::vector<int> res = {0, 0};

  while (res.back() < 1000 * 1000) {
    int m = res.size();
    int sum = 0;
    for (int i = 2; i < 2 * m; ++i) {
      if (!IsSquareNumber(m * m + i * i)) {
        continue;
      }
      if (i < m) {
        sum += i / 2;
      } else {
        sum += (2 * m - i) / 2 + 1;
      }
    }
    res.push_back(sum + res.back());
  }

  return res.size() - 1;
}
