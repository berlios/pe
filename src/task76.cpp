#include <vector>

#include "base/task.h"

int CountNumberOfPartitions(int remaining, std::vector<int>* sequence) {
  if (remaining == 0) {
    return 1;
  }

  int sum = 0;
  int max = sequence->back();
  for (int i = 1; i <= max && i <= remaining; ++i) {
    sequence->push_back(i);
    sum += CountNumberOfPartitions(remaining - i, sequence);
    sequence->pop_back();
  }

  return sum;
}

TASK(76) {
  int counter = 0;
  for (int i = 1; i < 100; ++i) {
    std::vector<int> sequence = {i};
    counter += CountNumberOfPartitions(100 - i, &sequence);
  }
  return counter;
}
