#include <algorithm>
#include <unordered_map>

#include "base/pythagorean_triple.h"
#include "base/task.h"

void Task75DFS(const PrimitivePythagoreanTriple<int> &triple, int max_perimeter,
               std::unordered_map<int, int> *m) {
  int perimeter = triple.Perimeter();
  if (perimeter > max_perimeter) {
    return;
  }

  for (int i = 1; i <= max_perimeter / perimeter; ++i) {
    (*m)[perimeter * i]++;
  }

  Task75DFS(triple.PriceTree().LeftChild(), max_perimeter, m);
  Task75DFS(triple.PriceTree().MiddleChild(), max_perimeter, m);
  Task75DFS(triple.PriceTree().RightChild(), max_perimeter, m);
}

TASK(75) {
  std::unordered_map<int, int> m;
  PrimitivePythagoreanTriple<int> root(3, 4, 5);
  Task75DFS(root, 1500 * 1000, &m);

  return std::count_if(m.begin(), m.end(),
                       [](const auto &pair) { return pair.second == 1; });
}
