#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  scene_ = new Scene();
  ui->setupUi(this);
  ui->baseGV->setScene(scene_);
  ui->tab_3->setTabText(0, "Maze");
  ui->tab_3->setTabText(1, "Cave");
  QRect rcontent = ui->baseGV->contentsRect();
  ui->baseGV->setSceneRect(0, 0, rcontent.width(), rcontent.height());
  // cave connecitons
  connect(this, SIGNAL(sendPathToLoadCave(QString)), scene_,
          SLOT(GetFilepathToLoadCave(QString)));
  connect(ui->randomCaveButton, SIGNAL(clicked(bool)), this,
          SLOT(RandomCaveSlot()));
  connect(this, SIGNAL(sendRandomCaveValues(int, int, int, int, float)), scene_,
          SLOT(GetRandomCaveValues(int, int, int, int, float)));
  connect(ui->nextStepButton, SIGNAL(clicked(bool)), scene_,
          SLOT(NextStepButtonClicked()));
  connect(ui->getCavePathButton, SIGNAL(clicked(bool)), this,
          SLOT(ReceiveFilePath()));
  connect(ui->saveCaveButton, SIGNAL(clicked()), scene_, SLOT(SaveCave()));
  connect(ui->AutoEvolvButton, SIGNAL(clicked()), this,
          SLOT(AutoEvolveButtonClicked()));
  connect(this, SIGNAL(sendTimeForEvolve(int)), scene_,
          SLOT(AutoEvolveSlot(int)));
  // maze connections
  connect(ui->loadFileButton, SIGNAL(clicked(bool)), this,
          SLOT(ReceiveFilePath()));
  connect(this, SIGNAL(sendPathToLoadMaze(QString)), scene_,
          SLOT(GetFilepathToLoadMaze(QString)));
  connect(ui->GenerateMazeButton, SIGNAL(clicked(bool)), this,
          SLOT(GenerateMaze()));
  connect(this, SIGNAL(sendMazeSizeToScene(int)), scene_,
          SLOT(GenerateRandomMaze(int)));
  connect(ui->saveMazeButton, SIGNAL(clicked()), scene_, SLOT(SaveMaze()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ReceiveFilePath() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Откройте maze файл"), tr("/Users"));
  QPushButton *senderButton = dynamic_cast<QPushButton *>(sender());
  if (senderButton->text() == "Load File") {
    emit sendPathToLoadMaze(filename);
  } else {
    emit sendPathToLoadCave(filename);
  }
}
// This could be done better
void MainWindow::RandomCaveSlot() {
  int x = ui->caveXspnBox->value();
  int y = ui->caveYspnBox->value();

  int birth = ui->birthSpinBox->value();
  int death = ui->deathSpinBox->value();

  float chance = ui->chanceSpinBox->value();

  emit sendRandomCaveValues(x, y, birth, death, chance);
}

void MainWindow::GenerateMaze() {
  emit sendMazeSizeToScene(ui->SizeSpinBox->value());
}

void MainWindow::AutoEvolveButtonClicked() {
  emit sendTimeForEvolve(ui->timeSpinBox->value());
}
