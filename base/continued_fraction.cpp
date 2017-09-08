#include "base/continued_fraction.h"

#include <iostream>

mpq_class FiniteNumberSequenceToFraction(const std::vector<int>& sequence) {
  mpq_class result = sequence.back();

  for (auto i = sequence.rbegin() + 1; i != sequence.rend(); ++i) {
    result = *i + (1/result);
  }

  return result;
}
