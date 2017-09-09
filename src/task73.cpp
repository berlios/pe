#include "base/task.h"

struct Node {
  std::pair<int, int> left;
  std::pair<int, int> right;
};

void SternBrocotDFS(const Node& node, int denominator_limit, int* counter) {
  if (node.left.second + node.right.second > denominator_limit) {
    return;
  }

  std::pair<int, int> mid = {node.left.first + node.right.first,
                             node.left.second + node.right.second};

  if (mid.second < 3 * mid.first && mid.second > 2 * mid.first) {
    (*counter)++;
  }
  if (mid.second < 3 * mid.first) {
    SternBrocotDFS({node.left, mid}, denominator_limit, counter);
  }
  if (mid.second > 2 * mid.first) {
    SternBrocotDFS({mid, node.right}, denominator_limit, counter);
  }
}

TASK(73) {
  int counter = 0;
  Node root = {{0, 1}, {1, 1}};
  SternBrocotDFS(root, 12000, &counter);
  return counter;
}
