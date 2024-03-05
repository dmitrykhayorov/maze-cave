
#include "writer.h"

Writer::Writer() { fileToWriteIn = ""; }

Writer::Writer(std::string path) {
  fileToWriteIn = "";
  SetFilepath(path);
}

void Writer::SetFilepath(std::string path) {
  std::ofstream out(path);
  if (!out.is_open()) {
    throw std::invalid_argument("Неверный путь к файлу для записи");
  }
  out.close();
  fileToWriteIn = path;
}

void Writer::WriteMazeToFile(s21::maze_t &maze) {
  if (fileToWriteIn == "") {
    return;
  }

  std::ofstream out(fileToWriteIn);

  out << maze.rows << ' ' << maze.cols << std::endl;

  for (int i = 0; i < maze.rows; i++) {
    for (int j = 0; j < maze.cols; j++) {
      out << maze.mazeRightBorder[i][j];
      if (j != maze.cols - 1) {
        out << ' ';
      }
    }
    out << std::endl;
  }

  out << std::endl;

  for (int i = 0; i < maze.rows; i++) {
    for (int j = 0; j < maze.cols; j++) {
      out << maze.mazeBottomBorder[i][j];
      if (j != maze.cols - 1) {
        out << ' ';
      }
    }
    out << std::endl;
  }
}

void Writer::WriteCaveToFile(s21::cave_t &cave) {
  if (fileToWriteIn == "") {
    return;
  }

  std::ofstream out(fileToWriteIn);

  out << cave.rows << ' ' << cave.cols << std::endl;

  for (int i = 0; i < cave.rows; i++) {
    for (int j = 0; j < cave.cols; j++) {
      out << cave.cave[i][j];
      if (j != cave.cols - 1) {
        out << ' ';
      }
    }
    out << std::endl;
  }
}