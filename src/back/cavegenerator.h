#ifndef MAZE_SRC_BACK_CAVEGENERATOR_H
#define MAZE_SRC_BACK_CAVEGENERATOR_H

#include <random>

#include "parser.h"
#include "solver.h"

namespace s21 {

/**
 * @brief класс для генерации уникальных cave
 *
 */
class CaveGenerator {
 public:
  /**
   * @brief Конструктор по умолчанию для генератора Cave
   *
   */
  CaveGenerator();
  /**
   * @brief Конструктор для генератора Cave
   *
   * @param x
   * @param y
   * @param birht
   * @param death
   * @param chance
   */
  CaveGenerator(int x, int y, int birht, int death, float chance = 1.f);
  /**
   * @brief Деструктор для генератора Cave
   *
   */
  ~CaveGenerator();
  /**
   * @brief Получить сгенерированный Cave
   *
   * @return cave_t сгенерированный Cave
   */
  cave_t InitRandomCave();
  /**
   * @brief Функция улучшения Cave
   *
   * @param cave Cave для улучшения
   * @param birhtLimit Лимит рождения
   * @param deathLimit Лимит смерти
   */
  void UpdateStateOfCave(cave_t &cave, int birhtLimit, int deathLimit);

 private:
  void AllocateCave();
  void AllocateCave(cave_t &cave);
  int CountAliveNeighbors(const cave_t &cave, int x, int y);

 private:
  int x_, y_;
  cave_t cave_;
  int birthLimit_;
  int deathLimit_;
  float probability_;
};

}  // namespace s21
#endif
