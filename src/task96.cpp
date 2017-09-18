#include <cctype>

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "base/common.h"
#include "base/task.h"
#include "gtest/gtest.h"

namespace {

class SudokuCell {
 public:
  SudokuCell() : is_set_(false) { ResetPossibleValues(); }
  SudokuCell(int value) { SetValue(value); }

  void SetValue(int new_value) {
    if (new_value == 0) {
      is_set_ = false;
      ResetPossibleValues();
      value_ = 0;
      return;
    }

    is_set_ = true;
    value_ = new_value;
    possible_values_.clear();
  }

  bool RemovePossibleValue(int value) {
    auto it =
        std::remove(possible_values_.begin(), possible_values_.end(), value);

    bool removed_something = (it != possible_values_.end());
    possible_values_.erase(it, possible_values_.end());
    return removed_something;
  }

  const std::vector<int>& possible_values() const { return possible_values_; }
  bool is_set() const { return is_set_; }
  int value() const { return value_; }

 private:
  void ResetPossibleValues() { possible_values_ = {1, 2, 3, 4, 5, 6, 7, 8, 9}; }

  int value_;
  bool is_set_;
  std::vector<int> possible_values_;
};

class SudokuBoard {
 public:
  void SetFromString(const std::string& str) {
    int i = 0, j = 0;
    for (char c : str) {
      if (!isspace(c)) {
        board_[i][j].SetValue(c - '0');
        ++j;
        i += j / 9;
        j = j % 9;
      }
    }
  }

  bool TryFindSolution() {
    while (ReducePossibleValues()) {
      SetDefiniteValues();
    }

    return SolutionDFS();
  }

  std::string ToString() const {
    std::string result;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        result += std::to_string(board_[i][j].value());
      }
      if (i != 8) {
        result += '\n';
      }
    }
    return result;
  }

  bool AllValuesAreSet() const {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (!board_[i][j].is_set()) {
          return false;
        }
      }
    }
    return true;
  }

  bool CheckRules() const {
    // Check squares.
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        std::vector<int> values;
        for (int ii = 3 * i; ii < 3 * i + 3; ++ii) {
          for (int jj = 3 * j; jj < 3 * j + 3; ++jj) {
            if (board_[ii][jj].is_set()) {
              values.push_back(board_[ii][jj].value());
            }
          }
        }
        std::sort(values.begin(), values.end());
        if (std::unique(values.begin(), values.end()) != values.end()) {
          return false;
        }
      }
    }

    // Check rows.
    for (int i = 0; i < 9; ++i) {
      std::vector<int> values;
      for (int j = 0; j < 9; ++j) {
        if (board_[i][j].is_set()) {
          values.push_back(board_[i][j].value());
        }
      }
      std::sort(values.begin(), values.end());
      if (std::unique(values.begin(), values.end()) != values.end()) {
        return false;
      }
    }

    // Check columns.
    for (int j = 0; j < 9; ++j) {
      std::vector<int> values;
      for (int i = 0; i < 9; ++i) {
        if (board_[i][j].is_set()) {
          values.push_back(board_[i][j].value());
        }
      }
      std::sort(values.begin(), values.end());
      if (std::unique(values.begin(), values.end()) != values.end()) {
        return false;
      }
    }

    return true;
  }

  int operator()(int i, int j) const { return board_[i][j].value(); }

 private:
  bool SolutionDFS() {
    if (NoMorePossibilities()) {
      return false;
    }

    if (!CheckRules()) {
      return false;
    }

    if (AllValuesAreSet()) {
      return true;
    }

    auto cell_coordinates = GetUnsetCellCoordinates();
    int i = cell_coordinates.first;
    int j = cell_coordinates.second;

    auto possible_values = board_[i][j].possible_values();
    for (int value : possible_values) {
      auto new_board = *this;
      // new_board.board_[i][j].SetValue(value);
      if (!new_board.SetValue(i, j, value)) {
        continue;
      }
      if (new_board.TryFindSolution()) {
        *this = new_board;
        return true;
      }
    }

    return false;
  }

  bool NoMorePossibilities() const {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        const SudokuCell& cell = board_[i][j];
        if (!cell.is_set() && cell.possible_values().empty()) {
          return true;
        }
      }
    }
    return false;
  }

  std::pair<int, int> GetUnsetCellCoordinates() const {
    int result_i = -1, result_j = -1;
    size_t min_possibilities = 11;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        const SudokuCell& cell = board_[i][j];
        if (cell.is_set()) {
          continue;
        }
        if (min_possibilities > cell.possible_values().size()) {
          min_possibilities = cell.possible_values().size();
          result_i = i;
          result_j = j;
        }
      }
    }

    return {result_i, result_j};
  }

  bool SetValue(int i, int j, int value) {
    board_[i][j].SetValue(value);
    std::vector<std::pair<int, int>> set_values;

    // Check row.
    for (int jj = 0; jj < 9; ++jj) {
      SudokuCell& cell = board_[i][jj];
      if (cell.is_set()) {
        continue;
      }
      cell.RemovePossibleValue(value);
      int number_of_possibilities = cell.possible_values().size();
      if (number_of_possibilities == 0) {
        return false;
      }
      if (number_of_possibilities == 1) {
        set_values.emplace_back(i, jj);
      }
    }

    // Check column.
    for (int ii = 0; ii < 9; ++ii) {
      SudokuCell& cell = board_[ii][j];
      if (cell.is_set()) {
        continue;
      }
      cell.RemovePossibleValue(value);
      int number_of_possibilities = cell.possible_values().size();
      if (number_of_possibilities == 0) {
        return false;
      }
      if (number_of_possibilities == 1) {
        set_values.emplace_back(ii, j);
      }
    }

    // Check square.
    for (int ii = (i / 3) * 3; ii < (i / 3) * 3 + 3; ++ii) {
      for (int jj = (j / 3) * 3; jj < (j / 3) * 3 + 3; ++jj) {
        SudokuCell& cell = board_[ii][jj];
        cell.RemovePossibleValue(value);
        if (cell.is_set()) {
          continue;
        }
        int number_of_possibilities = cell.possible_values().size();
        if (number_of_possibilities == 0) {
          return false;
        }
        if (number_of_possibilities == 1) {
          set_values.emplace_back(ii, jj);
        }
      }
    }

    for (const auto& pair : set_values) {
      if (!SetValue(pair.first, pair.second,
                    board_[pair.first][pair.second].possible_values()[0])) {
        return false;
      }
    }
    return true;
  }

  void SetDefiniteValues() {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board_[i][j].possible_values().size() == 1) {
          int value = board_[i][j].possible_values()[0];
          board_[i][j].SetValue(value);
        }
      }
    }
  }

  // Returns true if at least 1 value was reduced.
  bool ReducePossibleValues() {
    bool removed_something = false;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (!board_[i][j].is_set()) {
          continue;
        }
        int value = board_[i][j].value();
        if (RemovePossibleValueFromSquare(i / 3, j / 3, value)) {
          removed_something = true;
        }
        if (RemovePossibleValueFromRow(i, value)) {
          removed_something = true;
        }
        if (RemovePossibleValueFromColumn(j, value)) {
          removed_something = true;
        }
      }
    }
    return removed_something;
  }

  bool RemovePossibleValueFromRow(int i, int value) {
    bool removed_something = false;
    for (int j = 0; j < 9; ++j) {
      SudokuCell& cell = board_[i][j];
      if (!cell.is_set() && cell.RemovePossibleValue(value)) {
        removed_something = true;
      }
    }
    return removed_something;
  }

  bool RemovePossibleValueFromColumn(int j, int value) {
    bool removed_something = false;
    for (int i = 0; i < 9; ++i) {
      SudokuCell& cell = board_[i][j];
      if (!cell.is_set() && cell.RemovePossibleValue(value)) {
        removed_something = true;
      }
    }
    return removed_something;
  }

  bool RemovePossibleValueFromSquare(int i, int j, int value) {
    bool removed_something = false;
    for (int ii = 3 * i; ii < 3 * i + 3; ++ii) {
      for (int jj = 3 * j; jj < 3 * j + 3; ++jj) {
        SudokuCell& cell = board_[ii][jj];
        if (!cell.is_set() && cell.RemovePossibleValue(value)) {
          removed_something = true;
        }
      }
    }
    return removed_something;
  }

  std::array<std::array<SudokuCell, 9>, 9> board_;
};
}

TEST(Task96, SudokuBoard) {
  SudokuBoard board;
  std::string init_string =
      "003020600\n"
      "900305001\n"
      "001806400\n"
      "008102900\n"
      "700000008\n"
      "006708200\n"
      "002609500\n"
      "800203009\n"
      "005010300";

  board.SetFromString(init_string);
  EXPECT_EQ(init_string, board.ToString());
  EXPECT_EQ(0, board(0, 0));
  EXPECT_EQ(3, board(0, 2));
  EXPECT_FALSE(board.AllValuesAreSet());

  EXPECT_TRUE(board.TryFindSolution());
  EXPECT_TRUE(board.AllValuesAreSet());

  EXPECT_EQ(
      "483921657\n"
      "967345821\n"
      "251876493\n"
      "548132976\n"
      "729564138\n"
      "136798245\n"
      "372689514\n"
      "814253769\n"
      "695417382",
      board.ToString());
}

TEST(Task96, SudokuBoard2) {
  SudokuBoard board;
  std::string init_string =
      "000000907"
      "000420180"
      "000705026"
      "100904000"
      "050000040"
      "000507009"
      "920108000"
      "034059000"
      "507000000";

  board.SetFromString(init_string);

  EXPECT_TRUE(board.TryFindSolution());
  EXPECT_TRUE(board.AllValuesAreSet());
  EXPECT_TRUE(board.CheckRules());
}

TEST(Task96, SudokuBoard3) {
  SudokuBoard board;
  std::string init_string =
      "030050040"
      "008010500"
      "460000012"
      "070502080"
      "000603000"
      "040109030"
      "250000098"
      "001020600"
      "080060020";

  board.SetFromString(init_string);

  EXPECT_TRUE(board.TryFindSolution());
  EXPECT_TRUE(board.AllValuesAreSet());
  EXPECT_TRUE(board.CheckRules());
}

TASK(96) {
  auto lines =
      Split(ReadFileIntoString("data/096_sudoku.txt"), '\n', SkipEmpty());

  int result = 0;

  // Only lines from 10*k + 1 to 10*k + 9 inclusive contain sudoku puzzles.
  for (size_t k = 0; k <= (lines.size() - 9) / 10; ++k) {
    std::string puzzle;
    for (int i = 1; i <= 9; ++i) {
      puzzle += lines[k * 10 + i];
    }

    SudokuBoard board;
    board.SetFromString(puzzle);
    CHECK(board.TryFindSolution() == true);
    CHECK(board.CheckRules() == true);
    result += board(0, 0) * 100 + board(0, 1) * 10 + board(0, 2);
  }

  return result;
}
