#ifndef BASE_CONTINUED_FRACTION_H_
#define BASE_CONTINUED_FRACTION_H_

#include <gmpxx.h>
#include <vector>

mpq_class FiniteNumberSequenceToFraction(const std::vector<int> &sequence);

#endif  // BASE_CONTINUED_FRACTION_H_
