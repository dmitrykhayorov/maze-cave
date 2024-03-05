#include "controller.h"

maze_t Controller::InitMazeFromFile(QString filepath) {
  Parser mazeParcer{};
  try {
    mazeParcer.SetFilepathMaze(filepath.toStdString());
  } catch (const std::invalid_argument &err) {
    qDebug() << err.what();
    throw;
  }

  return mazeParcer.GetVectorsMaze();
}

solution_stack Controller::SolveMaze(point start, point end,
                                     const maze_t &Maze) {
  Solver<maze_t> solver;
  return solver.Solve(start, end, Maze);
}
solution_stack Controller::SolveCave(point start, point end,
                                     const cave_t &Cave) {
  Solver<cave_t> solver;
  return solver.Solve(start, end, Cave);
}
maze_t Controller::GenerateMaze(int size) {
  mazeGenerator generator;
  generator.GeneratePerfectMaze(size);

  return generator.GetVectorsMaze();
}
cave_t Controller::InitRandomCave(int x, int y, int birth, int death,
                                  float chance) {
  CaveGenerator cv(x, y, birth, death, chance);
  return cv.InitRandomCave();
}

void Controller::UpdateStateOfCave(cave_t &cave, int birthLimit,
                                   int deathLimit) {
  CaveGenerator cv;
  cv.UpdateStateOfCave(cave, birthLimit, deathLimit);
}

cave_t Controller::InitCaveFromFile(QString filepath) {
  Parser caveParser;
  caveParser.SetFilepathCave(filepath.toStdString());
  return caveParser.GetVectorsCave();
}

void Controller::SaveMaze(QString filepath, maze_t maze) {
  Writer writer(filepath.toStdString());
  writer.WriteMazeToFile(maze);
}

void Controller::SaveCave(QString filepath, cave_t cave) {
  Writer writer(filepath.toStdString());
  writer.WriteCaveToFile(cave);
}
