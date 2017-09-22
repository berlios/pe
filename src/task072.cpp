#include "base/number_theory.h"
#include "base/task.h"

TASK(72) {
  const int n = 1000*1000;
  auto primes = Sieve(n);

  std::vector<int> phi(n + 1);

  for (size_t i = 2; i <= n; ++i) {
    phi[i] = i;
  }

  for (int prime : primes) {
    if (prime > n) {
      break;
    }
    for (int i = 1; i <= n / prime; ++i) {
      phi[i*prime] /= prime;
      phi[i*prime] *= prime - 1;
    }
  }

  return std::accumulate(phi.begin() + 2, phi.end(), static_cast<int64_t>(0));
}
