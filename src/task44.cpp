#include <algorithm>
#include <gmpxx.h>
#include <vector>

#include "base/number_theory.h"
#include "base/task.h"

// This struct represents p(a + n) - p(a).
struct PentagonalDifference {
  PentagonalDifference(int n, int a)
      : n_(n), a_(a),
        value_(NthPentagonalNumber(a + n) - NthPentagonalNumber(a)) { }
  int n_;
  int a_;
  mpz_class value_;
};

TASK(44) {
  std::vector<PentagonalDifference> heap;

  auto cmp = [](const PentagonalDifference &first,
                const PentagonalDifference &second) {
               return first.value_ > second.value_;
             };
  auto heap_push = [&](int n, int a) {
                     heap.push_back(PentagonalDifference(n, a));
                     std::push_heap(heap.begin(), heap.end(), cmp);
                   };
  auto heap_pop = [&]() {
                    std::pop_heap(heap.begin(), heap.end(), cmp);
                    auto ret = heap.back();
                    heap.pop_back();
                    return ret;
                  };
  heap_push(1, 1);
  heap_push(2, 1);
  int current_max_n = 2;

  while (true) {
    auto min_difference = heap_pop();
    int a = min_difference.a_;
    int n = min_difference.n_;

    mpz_class sum = NthPentagonalNumber(a + n) + NthPentagonalNumber(a);
    if (IsPentagonalNumber(min_difference.value_) && IsPentagonalNumber(sum)) {
      return min_difference.value_;
    }

    heap_push(n, a + 1);
    if (current_max_n == n) {
      heap_push(n + 1, 1);
      current_max_n++;
    }
  }
}
