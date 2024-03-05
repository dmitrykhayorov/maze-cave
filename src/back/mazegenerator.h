#ifndef MAZE_SRC_BACK_MAZEGENERATOR_H
#define MAZE_SRC_BACK_MAZEGENERATOR_H

#include "parser.h"

namespace s21 {
/**
 * @brief Класс для генерации уникальных maze
 *
 */
class mazeGenerator : public s21::Parser {
 public:
  /**
   * @brief Конструктор по умолчанию для генератора уникальных maze
   *
   */
  mazeGenerator();
  /**
   * @brief Деструктор для генератора уникальных maze
   *
   */
  ~mazeGenerator();
  /**
   * @brief Функция, генерирующая уникальный maze
   *
   * @param size Размер матрицы maze
   */
  void GeneratePerfectMaze(int size);

 private:
  /**
   * @brief Функция по созданию стен в матрице maze
   *
   */
  void CreateWalls_();
  /**
   * @brief Функция по созданию правых стен в матрице maze
   *
   * @param row
   */
  void CreateRightWalls_(int row);
  /**
   * @brief Функция по созданию нижних стен в матрице maze
   *
   * @param row
   */
  void CreateBottomWalls_(int row);
  /**
   * @brief Функция по изменению нижнего ряда матрицы maze
   *
   */
  void ChangeLastRow_();
  /**
   * @brief Функция создающая вектор ряда после того, как сгенерированы правые
   * границы этого ряда
   *
   * @param row
   */
  void ChangeVectorWithNumsAfterBottom_(int row);
  /**
   * @brief Функция создающая вектор ряда после того, как сгенерированы нижние
   * границы этого ряда
   *
   * @param row
   */
  void ChangeVectorWithNumsAfterRight_(int row);

  /**
   * @brief Вектор ряда
   *
   */
  std::vector<int> row_with_nums_;
  /**
   * @brief Счётчик уникальных значений для добавления в вектор ряда
   *
   */
  int unique_counter_for_function_ChangeVectorWithNums_;
};
}  // namespace s21

#endif