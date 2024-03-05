#include "parser.h"

using namespace s21;

Parser::Parser() : rows_(0), cols_(0) {}

Parser::Parser(std::string filepath) : rows_(0), cols_(0), filepath_(filepath) {
  ReadMazeFromfile_();
}

Parser::~Parser() {
  ClearMemoryMaze_();
  ClearMemoryCave_();
}

//**********
//*  MAZE  *
//**********

void Parser::SetFilepathMaze(std::string filepath) {
  filepath_ = filepath;
  ReadMazeFromfile_();
}

void Parser::ReadMazeFromfile_() {
  std::string line_from_file;
  std::ifstream opened_file(filepath_);

  if (opened_file.fail()) {
    throw std::invalid_argument("Неверный путь к файлу");
  }
  if (std::getline(opened_file, line_from_file)) {
    GetRowsAndCols_(line_from_file);
  } else {
    throw std::invalid_argument("Файл пустой");
  }

  AllocateMemoryMaze_();

  for (int i = 0; i < rows_; i++) {
    if (!std::getline(opened_file, line_from_file)) {
      throw std::invalid_argument("Недостающее количество столбцов");
    } else {
      GetMazeRow_(line_from_file, 1, i);
    }
  }

  if (!std::getline(opened_file, line_from_file) || !line_from_file.empty()) {
    throw std::invalid_argument("Неверный формат записи maze");
  }

  for (int i = 0; i < rows_; i++) {
    if (!std::getline(opened_file, line_from_file)) {
      throw std::invalid_argument("Недостающее количество строк");
    } else {
      GetMazeRow_(line_from_file, 2, i);
    }
  }

  opened_file.close();
}

void Parser::GetRowsAndCols_(std::string line_from_file) {
  std::string::iterator it = line_from_file.begin();
  if (*it - '0' < 0 || *it - '0' > 9) {
    throw std::invalid_argument("Неверный формат записи количества столбцов");
  } else {
    while (*it - '0' >= 0 && *it - '0' <= 9) {
      rows_ = rows_ * 10 + *it - '0';
      it++;
    }
  }

  if (*it != ' ') {
    throw std::invalid_argument("Неверный формат записи maze/cave");
  }

  it++;

  if (*it - '0' < 0 || *it - '0' > 9) {
    throw std::invalid_argument("Неверный формат записи количества строк");
  } else {
    while (*it - '0' >= 0 && *it - '0' <= 9) {
      cols_ = cols_ * 10 + *it - '0';
      it++;
    }
  }
}

void Parser::GetMazeRow_(std::string line_from_file, int num_vector_to_fill,
                         int row) {
  std::string::iterator it = line_from_file.begin();
  for (int j = 0; j < cols_ && it != line_from_file.end(); j++) {
    if ((*it == '0' || *it == '1') &&
        ((it + 1) == line_from_file.end() || *(it + 1) == ' ')) {
      if (num_vector_to_fill == 1) {
        rightB_[row].push_back(*it - '0');
      } else {
        bottomB_[row].push_back(*it - '0');
      }
    } else {
      throw std::invalid_argument("Неверный формат записи maze");
    }
    it += 2;
  }

  if (num_vector_to_fill && rightB_[row].size() < (size_t)cols_) {
    throw std::invalid_argument("Неверный формат записи maze");
  } else if (!num_vector_to_fill && bottomB_[row].size() < (size_t)cols_) {
    throw std::invalid_argument("Неверный формат записи maze");
  }
}

void Parser::AllocateMemoryMaze_() {
  if (rows_ > 0 && cols_ > 0) {
    ClearMemoryMaze_();
    for (int i = 0; i < rows_; i++) {
      rightB_.push_back(std::vector<bool>());
      bottomB_.push_back(std::vector<bool>());
    }
  }
}

void Parser::ClearMemoryMaze_() {
  if (rows_ > 0 || cols_ > 0) {
    rightB_.clear();
    bottomB_.clear();
  }
}

maze_t Parser::GetVectorsMaze() { return {rightB_, bottomB_, cols_, rows_}; }

//**********
//*  CAVE  *
//**********

void Parser::SetFilepathCave(std::string filepath) {
  filepath_ = filepath;
  ReadCaveFromfile_();
}

void Parser::ReadCaveFromfile_() {
  std::string line_from_file;
  std::ifstream opened_file(filepath_);

  if (opened_file.fail()) {
    throw std::invalid_argument("Неверный путь к файлу");
  }

  if (std::getline(opened_file, line_from_file)) {
    GetRowsAndCols_(line_from_file);
  } else {
    throw std::invalid_argument("Файл пустой");
  }

  AllocateMemoryCave_();

  for (int i = 0; i < rows_; i++) {
    if (!std::getline(opened_file, line_from_file)) {
      throw std::invalid_argument("Недостающее количество строк");
    } else {
      GetCaveRow_(line_from_file, i);
    }
  }
}

void Parser::GetCaveRow_(std::string line_from_file, int row) {
  std::string::iterator it = line_from_file.begin();
  for (int j = 0; j < cols_ && it != line_from_file.end(); j++) {
    if ((*it == '0' || *it == '1') &&
        ((it + 1) == line_from_file.end() || *(it + 1) == ' ')) {
      cave_[row].push_back(*it - '0');
    } else {
      throw std::invalid_argument("Неверный формат записи cave");
    }
    it += 2;
  }

  if (cave_[row].size() < (size_t)cols_) {
    throw std::invalid_argument("Неверный формат записи cave");
  }
}

void Parser::AllocateMemoryCave_() {
  if (rows_ > 0 && cols_ > 0) {
    ClearMemoryCave_();
    for (int i = 0; i < rows_; i++) {
      cave_.push_back(std::vector<bool>());
    }
  }
}

void Parser::ClearMemoryCave_() {
  if (rows_ > 0 && cols_ > 0) {
    cave_.clear();
  }
}

cave_t Parser::GetVectorsCave() { return {cols_, rows_, cave_}; }
