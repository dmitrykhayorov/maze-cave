#include "mazegenerator.h"

using namespace s21;

mazeGenerator::mazeGenerator() {
  rows_ = 0;
  cols_ = 0;
}

mazeGenerator::~mazeGenerator() {}

void mazeGenerator::GeneratePerfectMaze(int size) {
  if (size < 1 || size > 50) {
    throw std::invalid_argument("Неверный размер maze");
  }

  unique_counter_for_function_ChangeVectorWithNums_ = 0;
  ClearMemoryMaze_();
  rows_ = size;
  cols_ = size;
  AllocateMemoryMaze_();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      rightB_[i].push_back(0);
      bottomB_[i].push_back(0);
    }
  }

  CreateWalls_();
}

void mazeGenerator::CreateWalls_() {
  std::random_device rd;   // obtain a random number from hardware
  std::mt19937 gen(rd());  // seed the generator
  std::uniform_int_distribution<> distr(0, 1);

  row_with_nums_.clear();

  for (int i = 0; i < rows_; i++) {
    CreateRightWalls_(i);
    if (i == 0) {
      unique_counter_for_function_ChangeVectorWithNums_++;
    }
    if (i != 0) {
      ChangeVectorWithNumsAfterRight_(i);
    }
    if (i != rows_ - 1) {
      CreateBottomWalls_(i);
      ChangeVectorWithNumsAfterBottom_(i);
    }
  }
  ChangeLastRow_();
}

void mazeGenerator::CreateRightWalls_(int row) {
  std::random_device rd;   // obtain a random number from hardware
  std::mt19937 gen(rd());  // seed the generator
  std::uniform_int_distribution<> distr(0, 1);

  for (int j = 0; j < cols_; j++) {
    if (row == 0) {
      row_with_nums_.push_back(
          unique_counter_for_function_ChangeVectorWithNums_);
      if (distr(gen) && j != cols_ - 1) {
        rightB_[row][j] = 1;
        unique_counter_for_function_ChangeVectorWithNums_++;
      }
    } else if (j != cols_ - 1) {
      if (row_with_nums_[j] == row_with_nums_[j + 1]) {
        rightB_[row][j] = 1;
      } else if (distr(gen)) {
        rightB_[row][j] = 1;
      }
    }
  }
}

void mazeGenerator::ChangeVectorWithNumsAfterRight_(int row) {
  int save_num = row_with_nums_[0];
  for (int j = 1; j < cols_; j++) {
    if (!rightB_[row][j - 1]) {
      save_num = row_with_nums_[j];
      row_with_nums_[j] = row_with_nums_[j - 1];
    } else if (save_num == row_with_nums_[j]) {
      row_with_nums_[j] = row_with_nums_[j - 1];
    } else {
      save_num = row_with_nums_[j];
    }
  }
}

void mazeGenerator::CreateBottomWalls_(int row) {
  bool flag_for_empty_space_in_the_row =
      false;  // флаг, показывающий наличие или отсутствие пустого пространства
              // между ячейками с одним номером
  bool same_num =
      false;  // создан, чтобы зайти в последнюю ячейку с одинаковым номером
  std::random_device rd;   // obtain a random number from hardware
  std::mt19937 gen(rd());  // seed the generator
  std::uniform_int_distribution<> distr(0, 3);

  for (int j = 0; j < cols_; j++) {
    if (j != cols_ - 1 && row_with_nums_[j] == row_with_nums_[j + 1]) {
      if (same_num && flag_for_empty_space_in_the_row && bottomB_[row][j - 1]) {
        bottomB_[row][j] = 1;
      } else if (distr(gen)) {
        bottomB_[row][j] = 1;
      } else {
        flag_for_empty_space_in_the_row = true;
      }
      same_num = true;
    } else if (same_num && flag_for_empty_space_in_the_row) {
      if (bottomB_[row][j - 1]) {
        bottomB_[row][j] = 1;
      } else if (distr(gen)) {
        bottomB_[row][j] = 1;
      }
      same_num = false;
    }

    if (j != cols_ - 1 && row_with_nums_[j] != row_with_nums_[j + 1]) {
      flag_for_empty_space_in_the_row = false;
    }
  }
}

void mazeGenerator::ChangeVectorWithNumsAfterBottom_(int row) {
  std::vector<int> buf;
  row_with_nums_.clear();

  for (int j = 0; j < cols_; j++) {
    if (!bottomB_[row][j]) {
      buf.push_back(row_with_nums_[j]);
    } else {
      buf.push_back(unique_counter_for_function_ChangeVectorWithNums_);
      unique_counter_for_function_ChangeVectorWithNums_++;
    }
  }

  row_with_nums_.clear();
  row_with_nums_ = buf;
}

void mazeGenerator::ChangeLastRow_() {
  for (int j = 0; j < cols_ - 1; j++) {
    if (row_with_nums_[j] != row_with_nums_[j + 1]) {
      rightB_[rows_ - 1][j] = 0;
    }
  }
}
