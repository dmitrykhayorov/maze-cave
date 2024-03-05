#ifndef MAZE_CONTROLLER_CONTROLLER_H
#define MAZE_CONTROLLER_CONTROLLER_H

#include <QDebug>
#include <QString>

#include "../back/cavegenerator.h"
#include "../back/mazegenerator.h"
#include "../back/parser.h"
#include "../back/solver.h"
#include "../back/writer.h"

using namespace s21;

/**
 * @brief Класс для
 *
 */
class Controller {
 public:
  /**
   * @brief Функция для получения maze из файла
   *
   * @param filepath Путь к файлу с maze
   * @return maze_t Maze из файла
   */
  maze_t InitMazeFromFile(QString filepath);
  /**
   * @brief Функция генерации уникального maze
   *
   * @param size Размер стороны матрицы
   * @return maze_t Сгенерированный maze
   */
  maze_t GenerateMaze(int size);
  /**
   * @brief Функция нахождения пути в maze
   *
   * @param start точка начала маршрута
   * @param end точка конца маршрута
   * @param Maze Maze, в котором ищется маршрут между точек
   * @return solution_stack Путь
   */
  solution_stack SolveMaze(point start, point end, const maze_t &Maze);
  /**
   * @brief Функция нахождения пути в maze
   *
   * @param start точка начала маршрута
   * @param end точка конца маршрута
   * @param Maze Cave, в котором ищется маршрут между точек
   * @return solution_stack Путь
   */
  solution_stack SolveCave(point start, point end, const cave_t &Cave);
  /**
   * @brief Создание случайного cave
   *
   * @param x строки
   * @param y столбцы
   * @param birth показатель "жизни"
   * @param death показатель "смерти"
   * @param chance вероятность инициализации клетки
   * @return cave_t Уникальный cave
   */
  cave_t InitRandomCave(int x, int y, int birth, int death, float chance);
  /**
   * @brief Функция для получения cave из файла
   *
   * @param filepath Путь к файлу с cave
   * @return maze_t Cave из файла
   */
  cave_t InitCaveFromFile(QString filepath);
  /**
   * @brief Функция снова использует алгоритм по оптимизации cave
   *
   * @param cave Cave для оптимизации
   * @param birthLimit показатель "жизни"
   * @param deathLimit показатель "смерти"
   */
  void UpdateStateOfCave(cave_t &cave, int birthLimit, int deathLimit);
  /**
   * @brief Функция записывает maze в файл
   *
   * @param filepath путь к файлу
   * @param maze maze для записи
   */
  void SaveMaze(QString filepath, maze_t maze);
  /**
   * @brief Функция записывает cave в файл
   *
   * @param filepath путь к файлу
   * @param maze cave для записи
   */
  void SaveCave(QString filepath, cave_t cave);
};

#endif
