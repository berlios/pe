#include <gmpxx.h>
#include <set>
#include <utility>

#include "base/task.h"

bool TrivialFraction(int numerator, int denominator) {
  // Since we consider only fractions with two digits in both numerator and
  // denominator we can safely throw out all fractions where any of numerator
  // or denominator ends with a zero.

  return (numerator % 10 == 0 || denominator % 10 == 0);
}

bool FractionCanBeCancelled(int numerator, int denominator) {
  if (numerator / 10 == denominator / 10 &&
      numerator*(denominator % 10) == denominator*(numerator % 10)) {
    return true;
  }

  if (numerator % 10 == denominator / 10 &&
      numerator*(denominator % 10) == denominator*(numerator / 10)) {
    return true;
  }

  if (numerator / 10 == denominator % 10 &&
      numerator*(denominator / 10) == denominator*(numerator % 10)) {
    return true;
  }

  if (numerator % 10 == denominator % 10 &&
      numerator*(denominator / 10) == denominator*(numerator / 10)) {
    return true;
  }

  return false;

}

TASK(33) {
  std::set<std::pair<int, int>> fractions;
  for (int numerator = 10; numerator < 100; ++numerator) {
    for (int denominator = 10; denominator < 100; ++denominator) {
      if (numerator < denominator &&
          !TrivialFraction(numerator, denominator) &&
          FractionCanBeCancelled(numerator, denominator)) {
        fractions.insert(std::make_pair(numerator, denominator));
      }
    }
  }

  // CHECK_EQ(4, fractions.size())

  mpq_class tmp = 1;
  for (auto &fraction : fractions) {
    tmp *= fraction.first;
    tmp /= fraction.second;
  }

  tmp.canonicalize();
  return tmp.get_den();
}
