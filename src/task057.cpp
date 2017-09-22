#include <gmpxx.h>
#include <vector>

#include "base/continued_fraction.h"
#include "base/task.h"

TASK(57) {
  std::vector<int> sequence{1, 2};
  int counter = 0;

  for (int i = 0; i < 1000; ++i) {
    mpq_class fraction = FiniteNumberSequenceToFraction(sequence);
    if (fraction.get_num().get_str().size() >
        fraction.get_den().get_str().size()) {
      ++counter;
    }
    sequence.push_back(2);
  }

  return counter;
}
