#include <algorithm>
#include <string>
#include <vector>

#include "base/common.h"
#include "base/task.h"
#include "gtest/gtest.h"

using std::string;
using std::vector;

// graph should have 1 int in first vector, 2 ints in second and etc.
// Finds max sum along the path from top to bottom.
int FindMaxSum(const vector<vector<int>> graph) {
  vector<vector<int>> sum_graph;
  sum_graph.resize(graph.size());
  for (size_t i = 0; i < sum_graph.size(); ++i) {
    sum_graph[i].resize(graph[i].size(), 0);
  }

  // Prepare bottom row.
  sum_graph.back() = graph.back();

  for (size_t i = graph.size() - 2; i != 0; --i) {
    for (size_t j = 0; j < graph[i].size(); ++j) {
      sum_graph[i][j] = std::max(graph[i][j] + sum_graph[i + 1][j],
                                 graph[i][j] + sum_graph[i + 1][j + 1]);
    }
  }

  sum_graph[0][0] = std::max(graph[0][0] + sum_graph[1][0],
                             graph[0][0] + sum_graph[1][1]);

  return sum_graph[0][0];
}

void ParseGraph(const string &str, vector<vector<int>> *graph) {
  graph->clear();

  vector<string> tmp = Split(str, '\n');
  graph->resize(tmp.size());

  for (size_t i = 0; i < tmp.size(); ++i) {
    vector<string> numbers = Split(tmp[i], ' ');
    for (size_t j = 0; j < numbers.size(); ++j) {
      (*graph)[i].push_back(std::stoi(numbers[j]));
    }
  }
}

TEST(Task18, ParseGraph) {
  string data = "3\n"
                "7 4\n"
                "2 4 6\n"
                "8 5 9 3";

  vector<vector<int>> graph;
  ParseGraph(data, &graph);

  EXPECT_EQ(4, graph.size());
  EXPECT_EQ(1, graph[0].size());
  EXPECT_EQ(2, graph[1].size());
  EXPECT_EQ(3, graph[2].size());
  EXPECT_EQ(4, graph[3].size());

  EXPECT_EQ(3, graph[0][0]);
  EXPECT_EQ(7, graph[1][0]);
  EXPECT_EQ(4, graph[1][1]);
  EXPECT_EQ(2, graph[2][0]);
  EXPECT_EQ(4, graph[2][1]);
  EXPECT_EQ(6, graph[2][2]);
  EXPECT_EQ(8, graph[3][0]);
  EXPECT_EQ(5, graph[3][1]);
  EXPECT_EQ(9, graph[3][2]);
  EXPECT_EQ(3, graph[3][3]);
}

TEST(Task18, FindMaxSum) {
  string data = "3\n"
                "7 4\n"
                "2 4 6\n"
                "8 5 9 3";

  vector<vector<int>> graph;
  ParseGraph(data, &graph);

  EXPECT_EQ(23, FindMaxSum(graph));
}

TASK(18) {
  string data = "75\n"
                "95 64\n"
                "17 47 82\n"
                "18 35 87 10\n"
                "20 04 82 47 65\n"
                "19 01 23 75 03 34\n"
                "88 02 77 73 07 63 67\n"
                "99 65 04 28 06 16 70 92\n"
                "41 41 26 56 83 40 80 70 33\n"
                "41 48 72 33 47 32 37 16 94 29\n"
                "53 71 44 65 25 43 91 52 97 51 14\n"
                "70 11 33 28 77 73 17 78 39 68 17 57\n"
                "91 71 52 38 17 14 91 43 58 50 27 29 48\n"
                "63 66 04 68 89 53 67 30 73 16 69 87 40 31\n"
                "04 62 98 27 23 09 70 98 73 93 38 53 60 04 23";

  vector<vector<int>> graph;
  ParseGraph(data, &graph);

  return FindMaxSum(graph);
}
