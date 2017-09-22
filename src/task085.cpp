#include <algorithm>
#include <map>

#include "base/number_theory.h"
#include "base/task.h"

TASK(85) {
  std::vector<int> triangle_numbers;
  const int N = 2 * 1000 * 1000;
  int k = 0;
  while (NthTriangleNumber(k) < N) {
    triangle_numbers.push_back(NthTriangleNumber(k).get_si());
    k++;
  }

  std::map<int, int> m;
  for (int i = 1; static_cast<size_t>(i) < triangle_numbers.size(); ++i) {
    int t = N / triangle_numbers[i];

    auto it =
        std::lower_bound(triangle_numbers.begin(), triangle_numbers.end(), t);
    int j = std::distance(triangle_numbers.begin(), it) - 1;

    m.emplace(triangle_numbers[j] * triangle_numbers[i], i * j);
    m.emplace(triangle_numbers[j + 1] * triangle_numbers[i], i * (j + 1));
  }

  auto it1 = m.lower_bound(N);
  auto it2 = it1;
  --it1;

  if (N - it1->first > it2->first - N) {
    return it2->second;
  }
  return it1->second;
}
