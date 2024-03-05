#ifndef MAZE_BACK_WRITER_H_
#define MAZE_BACK_WRITER_H_

#include "parser.h"

/**
 * @brief Класс для записи maze и cave в файл
 *
 */
class Writer {
 public:
  /**
   * @brief Конструктор по умолчанию для writer
   *
   */
  Writer();
  /**
   * @brief Конструктор для writer с путём к файлу для записи матриц
   *
   */
  Writer(std::string path);
  /**
   * @brief Функция установки пути к файлу
   *
   * @param path Путь
   */
  void SetFilepath(std::string path);
  /**
   * @brief Функция для записи maze в файл
   *
   * @param maze maze для записи
   */
  void WriteMazeToFile(s21::maze_t &maze);
  /**
   * @brief Функция для записи cave в файл
   *
   * @param maze cave для записи
   */
  void WriteCaveToFile(s21::cave_t &cave);

 private:
  /**
   * @brief Путь к файлу
   *
   */
  std::string fileToWriteIn;
};

#endif