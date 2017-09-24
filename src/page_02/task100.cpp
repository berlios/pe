#include <tuple>

#include "base/continued_fraction.h"
#include "base/number_theory.h"
#include "base/quadratic_rational.h"
#include "base/task.h"

namespace {
std::pair<mpz_class, mpz_class> FundamentalSolutionToNegativePellEquation(
    int d) {
  QuadraticRational t(d, 1, 0);
  std::vector<int> sequence;

  while (true) {
    int floor = t.Floor().get_si();
    sequence.push_back(floor);

    t -= t.Floor();
    t = t.Reciprocal();

    mpq_class convergent = FiniteNumberSequenceToFraction(sequence);
    if (convergent.get_num() * convergent.get_num() -
            convergent.get_den() * convergent.get_den() * d ==
        -1) {
      return {convergent.get_num(), convergent.get_den()};
    }
  }
}
}

// m - blue disks, n - total disks.
// P(2 blue disks) = m/n * ((m-1)/(n-1)) = 1/2
// 2m^2 - 2m - (n^2 - n) = 0
// m = (1 + sqrt(2n^2 - 2n + 1))/2
//
// So we want 2n^2 - 2n + 1 to be a square integer.
// 2n^2 - 2n + 1 - y^2 = 0
// n = (1 + sqrt(2y^2 - 1))/2
//
// So we want 2y^2 - 1 to be a square integer.
// 2y^2 - 1 = x^2
// x^2 - 2y^2 = -1
//
// Off to solving a negative Pell equation.
TASK(100) {
  mpz_class minimum;
  mpz_ui_pow_ui(minimum.get_mpz_t(), 10, 12);

  mpz_class x1, y1;
  std::tie(x1, y1) = FundamentalSolutionToNegativePellEquation(2);

  mpz_class x = x1, y = y1;
  while ((x + 1) / 2 <= minimum) {
    mpz_class old_x = x, old_y = y;
    x = x1 * old_x + 2 * y1 * old_y;
    y = x1 * old_y + y1 * old_x;
  }

  mpz_class n = (x + 1) / 2;
  n = 2 * n * n - 2 * n + 1;
  n = (1 + sqrt(n)) / 2;
  return n;
}
