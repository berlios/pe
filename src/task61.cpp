#include <algorithm>
#include <functional>
#include <unordered_set>
#include <vector>

#include "base/number_theory.h"
#include "base/task.h"

enum class NumberType {
  Triangle,
  Square,
  Pentagonal,
  Hexagonal,
  Heptagonal,
  Octagonal,
};

struct Node {
  int value;
  NumberType type;
};

bool FindCycleOfFixedLength(const std::vector<std::vector<int>>& graph,
                            const std::vector<Node>& numbers,
                            size_t cycle_length,
                            std::vector<int>* current_sequence) {
  if (current_sequence->size() == cycle_length) {
    int first = current_sequence->front();
    int last = current_sequence->back();
    if (std::find(graph[last].begin(), graph[last].end(), first) ==
        graph[last].end()) {
      return false;
    }
    return true;
  }

  for (int i : graph[current_sequence->back()]) {
    NumberType new_type = numbers[i].type;
    // Check that new type is not already in the sequence.
    if (std::find_if(current_sequence->begin(), current_sequence->end(),
                     [&numbers, &new_type](int index) {
                       return numbers[index].type == new_type;
                     }) != current_sequence->end()) {
      continue;
    }

    current_sequence->push_back(i);
    if (FindCycleOfFixedLength(graph, numbers, cycle_length,
                               current_sequence)) {
      return true;
    }
    current_sequence->pop_back();
  }
  return false;
}

TASK(61) {
  std::vector<Node> numbers;

  auto populate_with_numbers_of_type = [&numbers](
      std::function<mpz_class(uint)> nth_number, NumberType type) {
    int n = 1;
    while (true) {
      int num = nth_number(n).get_ui();
      if (1000 <= num && num < 10000) {
        numbers.push_back({num, type});
      }
      if (num >= 10000) {
        break;
      }
      n++;
    }
  };
  populate_with_numbers_of_type(NthTriangleNumber, NumberType::Triangle);
  populate_with_numbers_of_type(NthSquareNumber, NumberType::Square);
  populate_with_numbers_of_type(NthPentagonalNumber, NumberType::Pentagonal);
  populate_with_numbers_of_type(NthHexagonalNumber, NumberType::Hexagonal);
  populate_with_numbers_of_type(NthHeptagonalNumber, NumberType::Heptagonal);
  populate_with_numbers_of_type(NthOctagonalNumber, NumberType::Octagonal);

  std::vector<std::vector<int>> graph(numbers.size());
  for (size_t i = 0; i < numbers.size(); ++i) {
    for (size_t j = i + 1; j < numbers.size(); ++j) {
      if (numbers[i].type == numbers[j].type) {
        continue;
      }

      if (numbers[i].value % 100 == numbers[j].value / 100) {
        graph[i].push_back(j);
      }
      if (numbers[j].value % 100 == numbers[i].value / 100) {
        graph[j].push_back(i);
      }
    }
  }

  std::vector<int> cycle;
  for (size_t i = 0; i < numbers.size(); ++i) {
    cycle.clear();
    cycle.push_back(i);
    if (FindCycleOfFixedLength(graph, numbers, 6, &cycle)) {
      break;
    }
  }

  return std::accumulate(
      cycle.begin(), cycle.end(), 0,
      [&numbers](int sum, int i) { return sum + numbers[i].value; });
}
