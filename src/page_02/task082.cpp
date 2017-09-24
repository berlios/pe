#include <queue>

#include "base/common.h"
#include "base/task.h"

namespace {
struct Edge {
  Edge(int end_vertex, int weight) : end_vertex(end_vertex), weight(weight) {}
  int end_vertex;
  int weight;
};

struct QueueNode {
  QueueNode(int vertex, int distance) : vertex(vertex), distance(distance) {}
  int vertex;
  int distance;
};

struct QueueNodeCompare {
  bool operator()(const QueueNode& a, const QueueNode& b) {
    return a.distance > b.distance;
  }
};

int Dijkstra(const std::vector<std::vector<Edge>>& graph, int start, int end) {
  std::priority_queue<QueueNode, std::vector<QueueNode>, QueueNodeCompare>
      unvisited;
  std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
  distances[start] = 0;

  for (size_t i = 0; i < graph.size(); ++i) {
    unvisited.emplace(i, distances[i]);
  }

  while (!unvisited.empty()) {
    int vertex, distance;
    // A workaround for std::priority_queue's inability to correct weights.
    // Instead of correcting weights we insert a value with a new weight
    // and delay deletetion.
    do {
      vertex = unvisited.top().vertex;
      distance = unvisited.top().distance;
      unvisited.pop();
    } while (distance != distances[vertex] && !unvisited.empty());
    if (unvisited.empty()) {
      break;
    }

    for (const Edge& edge : graph[vertex]) {
      int d = distances[vertex] + edge.weight;
      if (d < distances[edge.end_vertex]) {
        distances[edge.end_vertex] = d;
        unvisited.emplace(edge.end_vertex, d);
      }
    }
  }

  return distances[end];
}
}

TASK(82) {
  auto rows =
      Split(ReadFileIntoString("data/082_matrix.txt"), '\n', SkipEmpty());
  const int n = rows.size();

  std::vector<std::vector<int>> matrix;
  for (const std::string& row : rows) {
    matrix.emplace_back();
    for (const std::string& weight_string : Split(row, ',')) {
      matrix.back().emplace_back(stoi(weight_string));
    }
    CHECK(matrix.back().size() == static_cast<size_t>(n));
  }
  CHECK(matrix.size() == static_cast<size_t>(n));

  auto matrix_to_graph = [n](int i, int j) { return n * i + j; };

  // Two extra vertices are the artificial source and sink.
  // graph[n*n] is the source.
  // graph[n*n + 1] is the sink.
  std::vector<std::vector<Edge>> graph(n * n + 2);
  const int source = n * n;
  const int sink = n * n + 1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - 1; ++j) {
      if (i != 0) {
        graph[matrix_to_graph(i, j)].emplace_back(matrix_to_graph(i - 1, j),
                                                  matrix[i][j]);
      }
      graph[matrix_to_graph(i, j)].emplace_back(matrix_to_graph(i, j + 1),
                                                matrix[i][j]);

      if (i != n - 1) {
        graph[matrix_to_graph(i, j)].emplace_back(matrix_to_graph(i + 1, j),
                                                  matrix[i][j]);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    graph[source].emplace_back(matrix_to_graph(i, 0), 0);
  }
  for (int i = 0; i < n; ++i) {
    graph[matrix_to_graph(i, n - 1)].emplace_back(sink, matrix[i][n - 1]);
  }

  return Dijkstra(graph, source, sink);
}
