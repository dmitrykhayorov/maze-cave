#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QString>
#include <QWidget>

#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void sendPathToLoadMaze(QString);
  void sendPathToLoadCave(QString);
  void sendMazeSizeToScene(int);
  void sendRandomCaveValues(int, int, int, int, float);
  void sendTimeForEvolve(int);

 public slots:
  void ReceiveFilePath();
  void GenerateMaze();
  void AutoEvolveButtonClicked();
  void RandomCaveSlot();

 private:
  Ui::MainWindow *ui;
  Scene *scene_;
};
#endif  // MAINWINDOW_H
