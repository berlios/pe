#include <cmath>

#include "base/task.h"

namespace {
bool CheckRightTriangle(int x1, int y1, int x2, int y2) {
  int side_0_1 = x1 * x1 + y1 * y1;
  int side_0_2 = x2 * x2 + y2 * y2;
  int side_1_2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
  if (side_0_1 == side_0_2 + side_1_2) {
    return true;
  }
  if (side_0_2 == side_0_1 + side_1_2) {
    return true;
  }
  if (side_1_2 == side_0_1 + side_0_2) {
    return true;
  }
  return false;
}
}

TASK(91) {
  int counter = 0;
  for (int x1 = 0; x1 <= 50; ++x1) {
    for (int y1 = 0; y1 <= 50; ++y1) {
      if (x1 == 0 && y1 == 0) {
        continue;
      }
      for (int y2 = y1 + 1; y2 <= 50; ++y2) {
        if (CheckRightTriangle(x1, y1, x1, y2)) {
          counter++;
        }
      }

      for (int x2 = x1 + 1; x2 <= 50; ++x2) {
        for (int y2 = 0; y2 <= 50; ++y2) {
          if (CheckRightTriangle(x1, y1, x2, y2)) {
            counter++;
          }
        }
      }
    }
  }
  return counter;
}
