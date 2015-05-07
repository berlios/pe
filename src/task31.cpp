#include "base/task.h"

static int CoinsToPennies(int two_pounds, int one_pound, int p50, int p20, int p10,
                      int p5, int p2, int p1) {
  return 200*two_pounds +
         100*one_pound +
         50*p50 +
         20*p20 +
         10*p10 +
         5*p5 +
         2*p2 +
         p1;
}

TASK(31) {
  int sum = 0;
  for (int two_pounds = 0; two_pounds <= 1; ++two_pounds) {
    for (int one_pound = 0; one_pound <= 2; ++one_pound) {
      for (int p50 = 0; p50 <= 200/50; ++p50) {
        for (int p20 = 0; p20 <= 200/20; ++p20) {
          for (int p10 = 0; p10 <= 200/10; ++p10) {
            for (int p5 = 0; p5 <= 200/5; ++p5) {
              for (int p2 = 0; p2 <= 200/2; ++p2) {
                for (int p1 = 0; p1 <= 200; ++p1) {
                  if (CoinsToPennies(two_pounds, one_pound, p50, p20, p10, p5,
                                     p2, p1) == 200) {
                    sum++;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  SetResult(ToString(sum));
}
