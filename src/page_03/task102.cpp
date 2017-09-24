#include <algorithm>
#include <array>

#include "base/common.h"
#include "base/task.h"
#include "gtest/gtest.h"

namespace {
struct Point {
  int x = 0;
  int y = 0;
};

double CrossProductFromOrigin(Point a, Point b) {
  return a.x * b.y - a.y * b.x;
}
bool TriangleContainsOrigin(Point a, Point b, Point c) {
  std::array<double, 3> cross_products;
  cross_products[0] = CrossProductFromOrigin(a, b);
  cross_products[1] = CrossProductFromOrigin(b, c);
  cross_products[2] = CrossProductFromOrigin(c, a);

  if (*std::min_element(cross_products.begin(), cross_products.end()) > 0) {
    return true;
  }

  if (*std::max_element(cross_products.begin(), cross_products.end()) < 0) {
    return true;
  }

  return false;
}
}

TEST(Task102, TriangleContainsOrigin) {
  EXPECT_TRUE(TriangleContainsOrigin({-340, 495}, {-153, -910}, {835, -947}));
  EXPECT_FALSE(TriangleContainsOrigin({-175, 41}, {-421, -714}, {574, -645}));
}

TASK(102) {
  auto lines =
      Split(ReadFileIntoString("data/102_triangles.txt"), '\n', SkipEmpty());

  int counter = 0;
  for (const auto& line : lines) {
    auto numbers = Split(line, ',');
    CHECK(numbers.size() == 6);

    std::vector<int> coordinates;

    std::transform(numbers.begin(), numbers.end(),
                   std::back_inserter(coordinates),
                   [](const std::string& s) { return std::stoi(s); });

    if (TriangleContainsOrigin({coordinates[0], coordinates[1]},
                               {coordinates[2], coordinates[3]},
                               {coordinates[4], coordinates[5]})) {
      counter += 1;
    }
  }

  return counter;
}
