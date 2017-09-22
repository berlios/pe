#include <algorithm>
#include <unordered_set>

#include "base/number_theory.h"
#include "base/task.h"

TASK(87) {
  const int N = 50 * 1000 * 1000;
  auto primes = Sieve(N);

  std::unordered_set<int> result;

  std::vector<int> squares, cubes, fourth_powers;
  for (int i = 0; primes[i] * primes[i] < N; ++i) {
    squares.push_back(primes[i] * primes[i]);
  }
  for (int i = 0; primes[i] * primes[i] * primes[i] < N; ++i) {
    cubes.push_back(primes[i] * primes[i] * primes[i]);
  }
  for (int i = 0; primes[i] * primes[i] * primes[i] * primes[i] < N; ++i) {
    fourth_powers.push_back(primes[i] * primes[i] * primes[i] * primes[i]);
  }

  for (int square : squares) {
    int remaining1 = N - square;
    for (int cube : cubes) {
      int remaining2 = remaining1 - cube;
      if (remaining2 <= 0) {
        break;
      }

      for (int fourth_power : fourth_powers) {
        int remaining3 = remaining2 - fourth_power;
        if (remaining3 <= 0) {
          break;
        }

        result.emplace(N - remaining3);
      }
    }
  }

  return result.size();
}
