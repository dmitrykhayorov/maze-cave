#ifndef MAZE_BACK_PARSER_H_
#define MAZE_BACK_PARSER_H_

#include <exception>
#include <fstream>
#include <random>
#include <string>
#include <vector>

namespace s21 {
using matrix = typename std::vector<std::vector<bool>>;
/**
 * @brief Структура, хранящая все данные для cave
 *
 */
typedef struct CaveSturcture {
  int cols;
  int rows;
  matrix cave;
} cave_t;

/**
 * @brief Структура, хранящая все данные для maze
 *
 */
typedef struct MazeSturcture {
  matrix mazeRightBorder;
  matrix mazeBottomBorder;
  int rows;
  int cols;
} maze_t;

/**
 * @brief класс для парсинга maze и cave из файла
 *
 */
class Parser {
 public:
  /**
   * @brief Конструктор для парсера с указанием пути к файлу с maze/cave
   *
   * @param filepath
   */
  Parser(std::string filepath);
  /**
   * @brief Конструктор по умолчанию для парсера
   *
   * @param filepath
   */
  Parser();
  /**
   * @brief Деструктор для парсера
   *
   */
  ~Parser();

  /**
   * @brief Функция для установки пути к файлу с maze
   *
   * @param filepath пути к файлу с maze
   */
  void SetFilepathMaze(std::string filepath);
  /**
   * @brief Функция для установки пути к файлу с cave
   *
   * @param filepath путь к файлу с cave
   */
  void SetFilepathCave(std::string filepath);
  /**
   * @brief Получение данных о спаршенном maze
   *
   * @return maze_t структура со всей информацией о cave
   */
  maze_t GetVectorsMaze();
  /**
   * @brief Получение данных о спаршенном cave
   *
   * @return cave_t структура со всей информацией о maze
   */
  cave_t GetVectorsCave();

 protected:
  /**
   * @brief Функция выделяет память под maze
   *
   */
  void AllocateMemoryMaze_();
  /**
   * @brief Функция чистит maze для записи нового maze
   *
   */
  void ClearMemoryMaze_();
  int rows_;
  int cols_;
  matrix rightB_;
  matrix bottomB_;

  /**
   * @brief Функция выделяет память под cave
   *
   */
  void AllocateMemoryCave_();
  /**
   * @brief Функция чистит maze для записи нового cave
   *
   */
  void ClearMemoryCave_();

 private:
  /**
   * @brief Функция, открывающая файл с maze
   *
   */
  void ReadMazeFromfile_();
  /**
   * @brief Функция считывающая количество строк и столбцов из таблицы
   *
   * @param line_from_file строка из файла
   */
  void GetRowsAndCols_(std::string line_from_file);
  /**
   * @brief Функция, считывающая стены из строки в матрицу
   *
   * @param line_from_file Строка из файла
   * @param num_vector Флаг, показывающий, в какую из матриц maze производить
   * запись значений
   * @param row Ряд, в который записывать значения
   */
  void GetMazeRow_(std::string line_from_file, int num_vector, int row);
  /**
   * @brief Функция, открывающая файл с cave
   *
   */
  void ReadCaveFromfile_();
  /**
   * @brief Функция, считывающая состояние клетки из строки в матрицу
   *
   * @param line_from_file Строка из файла
   * @param row Ряд, в который записывать значения
   */
  void GetCaveRow_(std::string line_from_file, int row);

  matrix cave_;
  std::string filepath_;
};
}  // namespace s21
#endif
