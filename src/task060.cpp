#include <algorithm>
#include <vector>

#include "base/number_theory.h"
#include "base/task.h"

bool CheckPrimes(int p1, int p2) {
  return IsPrime(mpz_class(std::to_string(p1) + std::to_string(p2))) &&
         IsPrime(mpz_class(std::to_string(p2) + std::to_string(p1)));
}

bool FindCliqueOfFixedSize(const std::vector<std::vector<int>>& graph,
                           size_t clique_size,
                           std::vector<int>* current_clique) {
  if (current_clique->size() == clique_size) {
    return true;
  }

  for (int candidate_index : graph[current_clique->back()]) {
    bool clique_increased = true;
    for (size_t i = 0; i < current_clique->size() - 1; ++i) {
      if (!std::binary_search(graph[(*current_clique)[i]].begin(),
                              graph[(*current_clique)[i]].end(),
                              candidate_index)) {
        clique_increased = false;
        break;
      }
    }
    if (clique_increased) {
      current_clique->push_back(candidate_index);
      if (FindCliqueOfFixedSize(graph, clique_size, current_clique)) {
        return true;
      }
      current_clique->pop_back();
    }
  }

  return false;
}

TASK(60) {
  // Increase upper limit until result is greater than 0 and hope that it has
  // the lowest possible sum.
  auto primes = Sieve(10000);

  std::vector<std::vector<int>> graph(primes.size());
  for (size_t i = 0; i < primes.size(); ++i) {
    for (size_t j = i + 1; j < primes.size(); ++j) {
      if (CheckPrimes(primes[i], primes[j])) {
        graph[i].push_back(j);
      }
    }
  }

  std::vector<int> index_sequence;
  const size_t clique_size = 5;

  for (size_t i = 0; i < primes.size(); ++i) {
    index_sequence.clear();
    index_sequence.push_back(i);
    if (FindCliqueOfFixedSize(graph, clique_size, &index_sequence)) {
      break;
    }
  }

  if (index_sequence.size() != clique_size) {
    return 0;
  }

  return std::accumulate(index_sequence.begin(), index_sequence.end(), 0,
                         [&primes](int sum, int i) { return sum + primes[i]; });
}
