#include <algorithm>
#include <vector>

#include "base/number_theory.h"
#include "base/task.h"

int CountPartitionsIntoPrimes(const std::vector<int>& primes, int remaining,
                              std::vector<int>* sequence) {
  if (remaining == 0) {
    return 1;
  }

  int sum = 0;
  int min = std::min(sequence->back(), remaining);
  for (int i = 0; primes[i] <= min; ++i) {
    sequence->push_back(primes[i]);
    sum += CountPartitionsIntoPrimes(primes, remaining - primes[i], sequence);
    sequence->pop_back();
  }

  return sum;
}

TASK(77) {
  auto primes = Sieve(1000);
  for (int n = 2;; ++n) {
    int sum = 0;
    for (int i = 0; primes[i] < n; ++i) {
      std::vector<int> sequence = {primes[i]};
      sum += CountPartitionsIntoPrimes(primes, n - sequence[0], &sequence);
    }

    if (sum > 5000) {
      return n;
    }
  }
}
