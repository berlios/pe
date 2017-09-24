#include <utility>

#include "base/task.h"

TASK(71) {
  std::pair<int, int> left = {0, 1};
  std::pair<int, int> right = {1, 1};

  while (true) {
    std::pair<int, int> mid = {left.first + right.first,
                               left.second + right.second};
    if (3 * mid.second <= 7 * mid.first) {
      right = mid;
    } else {
      if (mid.second > 1000*1000) {
        return left.first;
      }
      left = mid;
    }
  }
}
