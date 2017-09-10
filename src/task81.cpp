#include <algorithm>
#include <limits>
#include <string>
#include <vector>

#include "base/common.h"
#include "base/task.h"

namespace {
struct Node {
  Node(int new_weight) : weight(new_weight) {}
  int weight;
  int minimum_cost_to_end = std::numeric_limits<int>::max();
};
}

TASK(81) {
  auto rows =
      Split(ReadFileIntoString("data/081_matrix.txt"), '\n', SkipEmpty());
  const int n = rows.size();

  std::vector<std::vector<Node>> matrix;
  for (const std::string& row : rows) {
    matrix.emplace_back();
    for (const std::string& weight_string : Split(row, ',')) {
      matrix.back().emplace_back(stoi(weight_string));
    }
    CHECK(matrix.back().size() == static_cast<size_t>(n));
  }
  CHECK(matrix.size() == static_cast<size_t>(n));

  matrix.back().back().minimum_cost_to_end = matrix.back().back().weight;
  for (int i = n - 2; i >= 0; --i) {
    matrix.back()[i].minimum_cost_to_end =
        matrix.back()[i].weight + matrix.back()[i + 1].minimum_cost_to_end;
  }
  for (int i = n - 2; i >= 0; --i) {
    matrix[i].back().minimum_cost_to_end =
        matrix[i].back().weight + matrix[i + 1].back().minimum_cost_to_end;
  }

  for (int sum = 2 * n - 3; sum >= 0; --sum) {
    for (int i = std::min(n - 2, sum); i >= 0; --i) {
      int j = sum - i;
      if (j > n - 2) {
        break;
      }

      matrix[i][j].minimum_cost_to_end =
          matrix[i][j].weight + std::min(matrix[i + 1][j].minimum_cost_to_end,
                                         matrix[i][j + 1].minimum_cost_to_end);
    }
  }

  return matrix[0][0].minimum_cost_to_end;
}
