#include <cstdlib>

#include <algorithm>
#include <string>
#include <vector>

#include "base/task.h"
#include "gtest/gtest.h"

using std::max;
using std::string;
using std::vector;

// Warning. This function assumes that each number is exactly
// 2 characters wide and that they have exactly 1 character in between them.
std::string ExtractFromGridAsString(int i, int j, const string grid,
                                    int grid_size) {
  int start = (i*grid_size + j)*3;
  return grid.substr(start, 2);
}

// // This function does not check the string to contain only digits.
// // In fact, it doesn't check anything.
// void DeleteLeadingZeroes(string &str) {
//   size_t pos = str.find_first_not_of('0');
//   if (pos == string::npos) {
//     // If str contains only zeroes, one of them should be left.
//     str = "0";
//   } else {
//     str = str.substr(str.find_first_not_of('0'));
//   }
// }

// Clears grid vector.
void GetVectorGridFromString(const string grid_str, int grid_size,
                             vector<vector<int> > &grid) {
  grid.clear();
  grid.resize(grid_size);

  for (int i = 0; i < grid_size; ++i) {
    for (int j = 0; j < grid_size; ++j) {
      string tmp = ExtractFromGridAsString(i, j, grid_str, grid_size);
      DeleteLeadingZeroes(&tmp);

      grid[i].push_back(atoi(tmp.c_str()));
    }
  }
}

string MaxProductOfFourInRow() {
  const int grid_size = 20;
  string grid_str =
      "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08\n"
      "49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00\n"
      "81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65\n"
      "52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91\n"
      "22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80\n"
      "24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50\n"
      "32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70\n"
      "67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21\n"
      "24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72\n"
      "21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95\n"
      "78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92\n"
      "16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57\n"
      "86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58\n"
      "19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40\n"
      "04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66\n"
      "88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69\n"
      "04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36\n"
      "20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16\n"
      "20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54\n"
      "01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48\n";

  vector<vector<int> > grid;
  GetVectorGridFromString(grid_str, grid_size, grid);

  int max_prod = 0;
  // Check horisontally.
  for (int i = 0; i < grid_size - 3; ++i) {
    for (int j = 0; j < grid_size; ++j) {
      int prod = grid[i][j]*grid[i + 1][j]*grid[i + 2][j]*grid[i + 3][j];
      max_prod = max(max_prod, prod);
    }
  }

  // Check vertically.
  for (int i = 0; i < grid_size; ++i) {
    for (int j = 0; j < grid_size - 3; ++j) {
      int prod = grid[i][j]*grid[i][j + 1]*grid[i][j + 2]*grid[i][j + 3];
      max_prod = max(max_prod, prod);
    }
  }

  // Check diagonally top-left to bottom-right.
  for (int i = 0; i < grid_size - 3; ++i) {
    for (int j = 0; j < grid_size - 3; ++j) {
      int prod = grid[i][j]*grid[i + 1][j + 1]*
                 grid[i + 2][j + 2]*grid[i + 3][j + 3];
      max_prod = max(max_prod, prod);
    }
  }

  // Check diagonally top-right to bottom-left.
  for (int i = 3; i < grid_size; ++i) {
    for (int j = 0; j < grid_size - 3; ++j) {
      int prod = grid[i][j]*grid[i - 1][j + 1]*
                 grid[i - 2][j + 2]*grid[i - 3][j + 3];
      max_prod = max(max_prod, prod);
    }
  }

  return ToString(max_prod);
}

TEST(Task11, ExtractFromGridAsString) {
  string grid_str = "06 95 43\n"
                    "45 22 15\n"
                    "89 04 00\n";

  EXPECT_EQ("06", ExtractFromGridAsString(0, 0, grid_str, 3));
  EXPECT_EQ("22", ExtractFromGridAsString(1, 1, grid_str, 3));
  EXPECT_EQ("04", ExtractFromGridAsString(2, 1, grid_str, 3));
  EXPECT_EQ("00", ExtractFromGridAsString(2, 2, grid_str, 3));
}

TEST(Task11, GetVectorGridFromString) {
  string grid_str = "92 10 20 21\n"
                    "60 98 16 44\n"
                    "18 31 96 09\n"
                    "00 97 03 48\n";
  int grid_size = 4;
  vector<vector<int> > grid;

  GetVectorGridFromString(grid_str, grid_size, grid);
  for (int i = 0; i < grid_size; ++i) {
    for (int j = 0; j < grid_size; ++j) {
      string tmp_str = ExtractFromGridAsString(i, j, grid_str, grid_size);
      DeleteLeadingZeroes(&tmp_str);
      EXPECT_EQ(atoi(tmp_str.c_str()), grid[i][j]);
    }
  }
}

TASK(11) {
  SetResult(MaxProductOfFourInRow());
}
