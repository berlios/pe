#include <vector>

#include "base/common.h"
#include "base/task.h"

// Functions from task 18.
int FindMaxSum(const std::vector<std::vector<int>>& graph);
void ParseGraph(const std::string &str, std::vector<std::vector<int>> *graph);

TASK(67) {
  std::vector<std::vector<int>> graph;
  std::string file_contents = ReadFileIntoString("data/067_triangle.txt");

  // No empty rows allowed at the end.
  while (file_contents.back() == '\n') {
    file_contents.pop_back();
  }
  ParseGraph(file_contents, &graph);
  return FindMaxSum(graph);
}
