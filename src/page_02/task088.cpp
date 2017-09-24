#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "base/task.h"

namespace {
void DFS(int remaining, std::vector<int> *dividers,
         std::function<void(const std::vector<int> &)> callback) {
  if (remaining == 1) {
    callback(*dividers);
  }

  if (dividers->size() > 0 && remaining < dividers->back()) {
    return;
  }

  int min = 2;
  if (dividers->size() > 0) {
    min = dividers->back();
  }

  for (int i = min; i <= remaining; ++i) {
    if (remaining % i == 0) {
      dividers->push_back(i);
      DFS(remaining / i, dividers, callback);
      dividers->pop_back();
    }
  }
}
}

TASK(88) {
  constexpr int N = 12 * 1000;
  std::unordered_map<int, int> m;
  for (int n = 2; n <= 2 * N; ++n) {
    std::vector<int> dummy;
    DFS(n, &dummy, [&m, n](const std::vector<int> &dividers) {
      int sum = std::accumulate(dividers.begin(), dividers.end(), 0);
      if (n < sum) {
        return;
      }

      int length = dividers.size() + n - sum;
      if (length > N || length == 1) {
        return;
      }

      if (m[length] == 0) {
        m[length] = n;
      } else {
        m[length] = std::min(m[length], n);
      }
    });
  }

  std::unordered_set<int> set;
  for (const auto &pair : m) {
    CHECK(pair.first <= N);
    set.emplace(pair.second);
  }

  return std::accumulate(set.begin(), set.end(), 0);
}
