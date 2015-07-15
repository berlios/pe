#include <map>

#include "base/pythagorean_triple.h"
#include "base/task.h"

void DFS(const PrimitivePythagoreanTriple<uint> &triple,
         int max_p, std::map<int, int> *result) {
  int perimeter = triple.a() + triple.b() + triple.c();
  if (perimeter > max_p) {
    return;
  }

  for (int i = 1; i*perimeter <= max_p; ++i) {
    (*result)[i*perimeter]++;
  }

  DFS(triple.PriceTree().LeftChild(), max_p, result);
  DFS(triple.PriceTree().MiddleChild(), max_p, result);
  DFS(triple.PriceTree().RightChild(), max_p, result);
}

TASK(39) {
  int max_c = 1000;
  std::map<int, int> result;

  DFS(PrimitivePythagoreanTriple<uint>(3, 4, 5), max_c, &result);

  int max = 0, ans = -1;
  for (auto pair : result) {
    if (max < pair.second) {
      max = pair.second;
      ans = pair.first;
    }
  }

  return ans;
}
