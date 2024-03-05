#ifndef MAZE_SRC_BACK_SOLVER_H
#define MAZE_SRC_BACK_SOLVER_H
#include <queue>
#include <set>
#include <stack>
#include <typeindex>

#include "parser.h"

namespace s21 {
/**
 * @brief Алиас для пары, которая хранит в себе координаты точки
 */
using point = typename std::pair<int, int>;
/**
 * @brief Стэк из точек, который хранит в себе найденный путь
 */
using solution_stack = typename std::stack<point>;

/**
 * @brief  Экземпляр класса ищет путь в maze/cave
 *
 * @tparam T Шаблонный параметр для передачи maze/cave
 */
template <typename T>
class Solver {
 public:
  Solver() = default;
  /**
   * @brief Метод, который ищет путь в maze/cave
   * относительно двух заданных точек
   *
   * @param start Точка, из которой начинается путь
   * @param end Точка, в которую должны прийти
   * @param mzcv Шаблонный параметр для передачи ссылка на maze/cave
   * @return * solution_stack Найденный путь, записанный в стек
   */
  solution_stack Solve(point start, point end, const T &mzcv);

 private:
  /**
   * @brief Вспомогательная функция для поиска достпуных для посещения соседей в
   * maze
   *
   * @param p Текущая точка, у которой будем смотреть соседей
   * @param maze Ссылка на maze
   * @return std::vector<point> Вектор с точками, которые можно посетить
   */
  std::vector<point> DefineAccessableNeighbors(point p, const maze_t &maze);
  /**
   * @brief Вспомогательная функция для поиска достпуных для посещения соседей в
   * cave
   *
   * @param p Текущая точка, у которой будем смотреть соседей
   * @param maze Ссылка на cave
   * @return std::vector<point> Вектор с точками, которые можно посетить
   */
  std::vector<point> DefineAccessableNeighbors(point p, const cave_t &cave);
};

template <typename T>
solution_stack Solver<T>::Solve(point start, point end, const T &mzcv) {
  solution_stack res;
  std::vector<point> neighbors;
  std::queue<point> frontier;
  std::set<point> visited;
  frontier.push(start);
  visited.insert(start);
  // init prev matrix
  point prev[mzcv.cols][mzcv.rows];
  for (int i = 0; i < mzcv.cols; i++) {
    for (int j = 0; j < mzcv.rows; j++) {
      prev[i][j] = point(-1, -1);
    }
  }

  while (!frontier.empty()) {
    point curr = frontier.front();
    frontier.pop();

    if (curr == end) {
      while (curr != point(-1, -1)) {
        res.push(curr);
        curr = prev[curr.first][curr.second];
      }
      return res;
    }
    // this seems to be useless
    if (typeid(T) == typeid(maze_t) || typeid(T) == typeid(cave_t)) {
      neighbors = DefineAccessableNeighbors(curr, mzcv);
    }

    for (auto p : neighbors) {
      if (visited.count(p) == 0u) {
        visited.insert(p);
        frontier.push(p);
        prev[p.first][p.second] = curr;
      }
    }
    neighbors.clear();
  }

  res = solution_stack{};
  return res;
}
template <typename T>
std::vector<point> Solver<T>::DefineAccessableNeighbors(point p,
                                                        const maze_t &maze) {
  std::vector<point> neighbors;
  // check north
  if (p.second > 0 && !maze.mazeBottomBorder[p.second - 1][p.first]) {
    neighbors.push_back(point{p.first, p.second - 1});
  }
  // check south
  if (p.second < maze.cols - 1 && !maze.mazeBottomBorder[p.second][p.first]) {
    neighbors.push_back(point{p.first, p.second + 1});
  }
  // check west
  if (p.first > 0 && !maze.mazeRightBorder[p.second][p.first - 1]) {
    neighbors.push_back(point{p.first - 1, p.second});
  }
  // check east
  if (p.first < maze.rows - 1 && !maze.mazeRightBorder[p.second][p.first]) {
    neighbors.push_back(point{p.first + 1, p.second});
  }
  return neighbors;
}
template <typename T>
std::vector<point> Solver<T>::DefineAccessableNeighbors(point p,
                                                        const cave_t &cave) {
  std::vector<point> neighbors;
  int x = p.first, y = p.second;
  if (cave.cave.empty()) return neighbors;
  if (y >= cave.cols || y < 0) return neighbors;
  if (x >= cave.rows || x < 0) return neighbors;
  if (cave.cave[y][x]) {
    return neighbors;
  }

  for (int i = -1; i <= 1; ++i) {
    if (y + i < 0 || y + i >= cave.cols) continue;
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      if (x + j < 0 || x + j >= cave.rows) continue;
      int sum = i + j;
      if (sum == -2 || sum == 0 || sum == 2) continue;
      if (!cave.cave[y + i][x + j]) {
        neighbors.push_back(point{x + j, y + i});
      }
    }
  }

  return neighbors;
}
}  // namespace s21
#endif  // SOLVER_H
