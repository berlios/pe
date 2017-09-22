#include <limits>
#include <vector>

#include "base/number_theory.h"
#include "base/task.h"

TASK(70) {
  const int n = 10*1000*1000;
  auto primes = Sieve(n);

  std::vector<int> phi(n);

  for (size_t i = 2; i < n; ++i) {
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

  int result;
  double min_ratio = std::numeric_limits<double>::infinity();
  for (int i = 2; i < n; ++i) {
    std::string str_i = std::to_string(i);
    std::string str_phi_of_i = std::to_string(phi[i]);

    std::sort(str_i.begin(), str_i.end());
    std::sort(str_phi_of_i.begin(), str_phi_of_i.end());

    if (str_i != str_phi_of_i) {
      continue;
    }

    double ratio = static_cast<double>(i) / phi[i];
    if (min_ratio > ratio) {
      min_ratio = ratio;
      result = i;
    }
  }

  return result;
}
