#include "scene.h"

#include <QDebug>
Scene::Scene() : controller_(new Controller()), evolvTimer_(new QTimer(this)) {
  GenerateRandomMaze(50);
  connect(evolvTimer_, SIGNAL(timeout()), this, SLOT(UpdateAutoEvolve()));
}

Scene::~Scene() { delete controller_; }

void Scene::GetFilepathToLoadMaze(QString filepath) {
  try {
    maze_ = controller_->InitMazeFromFile(filepath);
    DrawMaze_();
  } catch (const std::invalid_argument& err) {
    QMessageBox msgBox;
    QString error = err.what();
    msgBox.setText(error);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
  }
}

void Scene::AutoEvolveSlot(int time) {
  if (cave_.cave.empty()) return;
  evolvTimer_->start(time);
}

void Scene::UpdateAutoEvolve() {
  static int count = 0;
  if (cave_.cave.empty()) {
    evolvTimer_->stop();
    return;
  }

  if (count < 10) {
    clear();
    controller_->UpdateStateOfCave(cave_, birthLimit_, deathLimit_);
    DrawCave_();
    count++;
  } else {
    count = 0;
    evolvTimer_->stop();
  }
}

void Scene::GetFilepathToLoadCave(QString filepath) {
  try {
    cave_ = controller_->InitCaveFromFile(filepath);
    DrawCave_();
  } catch (const std::invalid_argument& err) {
    QMessageBox msgBox;
    QString error = err.what();
    msgBox.setText(error);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
  }
}

void Scene::GenerateRandomMaze(int size) {
  try {
    maze_ = controller_->GenerateMaze(size);
    DrawMaze_();
  } catch (const std::invalid_argument& err) {
    QMessageBox msgBox;
    QString error = err.what();
    msgBox.setText(error);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
  }
}

void Scene::GetRandomCaveValues(int x, int y, int birht, int death,
                                float chance) {
  cave_ = controller_->InitRandomCave(x, y, birht, death, chance);
  maze_.mazeBottomBorder.clear();
  maze_.mazeRightBorder.clear();
  deathLimit_ = death;
  birthLimit_ = birht;
  DrawCave_();
}

void Scene::NextStepButtonClicked() {
  if (cave_.cave.empty()) return;
  clear();
  controller_->UpdateStateOfCave(cave_, birthLimit_, deathLimit_);
  DrawCave_();
}

void Scene::DrawCave_() {
  clear();

  maze_.mazeBottomBorder.clear();
  maze_.mazeRightBorder.clear();

  stepX_ = width_ / cave_.rows;
  stepY_ = height_ / cave_.cols;

  for (int i = 0; i < cave_.cols; ++i) {
    for (int j = 0; j < cave_.rows; ++j) {
      if (cave_.cave[i][j]) {
        addRect(stepX_ * j, stepY_ * i, stepX_, stepY_, QPen(Qt::black),
                QBrush(Qt::red));
      }
    }
  }
}

void Scene::DrawMaze_() {
  clear();
  cave_.cave.clear();
  stepX_ = width_ / maze_.rows;
  stepY_ = height_ / maze_.cols;
  QPen borderPen{};
  borderPen.setColor(Qt::red);
  borderPen.setWidth(2);
  addRect(0, 0, width_, height_, borderPen);

  for (int i = 0; i < maze_.cols; i++) {
    for (int j = 0; j < maze_.rows; j++) {
      if (maze_.mazeBottomBorder[i][j]) {
        addLine(stepX_ * (j), stepY_ * (i + 1), stepX_ * (j + 1),
                stepY_ * (i + 1), borderPen);
      }
      if (maze_.mazeRightBorder[i][j]) {
        addLine(stepX_ * (j + 1), stepY_ * (i), stepX_ * (j + 1),
                stepY_ * (i + 1), borderPen);
      }
    }
  }
}

void Scene::DrawSolutionMaze(int x, int y) {
  if (!isSecondPoint_) {
    clear();
    DrawMaze_();
    addEllipse(stepX_ * (x + 0.5) - 3, stepY_ * (y + 0.5) - 3, 6, 6,
               QPen(Qt::blue), QBrush(Qt::blue));
    isSecondPoint_ = true;
    firstPoint_ = point{x, y};
    qDebug() << "first point x: " << x << "y: " << y << '\n';
  } else {
    addEllipse(stepX_ * (x + 0.5) - 3, stepY_ * (y + 0.5) - 3, 6, 6,
               QPen(Qt::blue), QBrush(Qt::blue));
    isSecondPoint_ = false;
    qDebug() << "second pointx: " << x << "y: " << y << '\n';
    solution_stack path =
        controller_->SolveMaze(firstPoint_, point(x, y), maze_);
    DrawPath(path);
  }
}

void Scene::DrawSolutionCave(int x, int y) {
  if (!isSecondPoint_) {
    clear();
    DrawCave_();
    addEllipse(stepX_ * (x + 0.5) - 3, stepY_ * (y + 0.5) - 3, 6, 6,
               QPen(Qt::blue), QBrush(Qt::blue));
    isSecondPoint_ = true;
    firstPoint_ = point{x, y};
    qDebug() << "first point x: " << x << "y: " << y << '\n';
  } else {
    addEllipse(stepX_ * (x + 0.5) - 3, stepY_ * (y + 0.5) - 3, 6, 6,
               QPen(Qt::blue), QBrush(Qt::blue));
    isSecondPoint_ = false;
    qDebug() << "second pointx: " << x << "y: " << y << '\n';
    solution_stack path =
        controller_->SolveCave(firstPoint_, point(x, y), cave_);
    DrawPath(path);
  }
}
// TODO: Add check for empty maze
void Scene::DrawSolution(int x, int y) {
  if (!maze_.mazeBottomBorder.empty() && !maze_.mazeRightBorder.empty()) {
    DrawSolutionMaze(x, y);
  } else if (!cave_.cave.empty()) {
    DrawSolutionCave(x, y);
  }
}

void Scene::DrawPath(solution_stack path) {
  if (path.empty()) {
    qDebug() << "solution_stack is empty";
  }
  //    path.pop();
  while (path.size() > 1) {
    point p0 = path.top();
    path.pop();
    point p1 = path.top();
    QPen linePen;
    linePen.setWidth(2);
    //        addEllipse(stepX_ * (p.first + 0.5) - 3, stepY_ * (p.second + 0.5)
    //        - 3, 6, 6, QPen(Qt::black), QBrush(Qt::black));
    addLine(stepX_ * (p0.first + 0.5), stepY_ * (p0.second + 0.5),
            stepX_ * (p1.first + 0.5), stepY_ * (p1.second + 0.5), linePen);
  }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  DrawSolution(event->scenePos().x() / stepX_, event->scenePos().y() / stepY_);
}

void Scene::SaveMaze() {
  try {
    QString filename = QFileDialog::getOpenFileName(
        nullptr, tr("Откройте файл для записи maze"), tr("/$HOME"));
    controller_->SaveMaze(filename, maze_);
  } catch (const std::invalid_argument& err) {
    QMessageBox msgBox;
    QString error = err.what();
    msgBox.setText(error);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
  }
}

void Scene::SaveCave() {
  try {
    QString filename = QFileDialog::getOpenFileName(
        nullptr, tr("Откройте файл для записи cave"), tr("/Users"));
    controller_->SaveCave(filename, cave_);
  } catch (const std::invalid_argument& err) {
    QMessageBox msgBox;
    QString error = err.what();
    msgBox.setText(error);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
  }
}
