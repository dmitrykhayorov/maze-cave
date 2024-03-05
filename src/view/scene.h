#ifndef MAZE_SRC_VIEW_SCENE_H
#define MAZE_SRC_VIEW_SCENE_H

#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <chrono>
#include <iostream>
#include <thread>

#include "../controller/controller.h"

using namespace s21;

class Scene : public QGraphicsScene {
  Q_OBJECT
 public:
  Scene();
  ~Scene();

 public slots:
  void GetFilepathToLoadMaze(QString);
  void GetFilepathToLoadCave(QString);
  void AutoEvolveSlot(int);
  void GenerateRandomMaze(int size);
  void GetRandomCaveValues(int, int, int, int, float);
  void NextStepButtonClicked();
  void SaveMaze();
  void SaveCave();

 private slots:
  void UpdateAutoEvolve();

 private:
  void DrawMaze_();
  void DrawCave_();
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void DrawSolution(int x, int y);
  void DrawSolutionMaze(int x, int y);
  void DrawSolutionCave(int x, int y);
  void DrawPath(solution_stack path);

 private:
  Controller* controller_;
  const double height_ = 500, width_ = 500;
  double stepX_, stepY_;
  maze_t maze_;
  cave_t cave_;
  bool isSecondPoint_;
  point firstPoint_;
  int deathLimit_, birthLimit_;
  QTimer* evolvTimer_;
};

#endif  // SCENE_H
