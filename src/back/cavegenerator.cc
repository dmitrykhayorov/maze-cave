#include "cavegenerator.h"

using namespace s21;

CaveGenerator::CaveGenerator() {}

CaveGenerator::CaveGenerator(int x, int y, int birht, int death, float chance)
    : x_(x),
      y_(y),
      birthLimit_(birht),
      deathLimit_(death),
      probability_(chance) {
  (void)birthLimit_;
  (void)deathLimit_;
}

CaveGenerator::~CaveGenerator() {}

cave_t CaveGenerator::InitRandomCave() {
  std::random_device rd;
  std::bernoulli_distribution dist{probability_};

  AllocateCave();
  // fill cave with random values
  for (int i = 0; i < y_; ++i) {
    for (int j = 0; j < x_; ++j) {
      cave_.cave[i].push_back(dist(rd));
    }
  }
  cave_.cols = y_;
  cave_.rows = x_;

  return cave_;
}

void CaveGenerator::UpdateStateOfCave(cave_t& cave, int birhtLimit,
                                      int deathLimit) {
  cave_t updatedCave;
  updatedCave.cols = cave.cols;
  updatedCave.rows = cave.rows;

  AllocateCave(updatedCave);

  for (int i = 0; i < cave.cols; ++i) {
    for (int j = 0; j < cave.rows; ++j) {
      int numOfNeighbors = CountAliveNeighbors(cave, j, i);
      if (cave.cave[i][j]) {
        if (numOfNeighbors < deathLimit) {
          updatedCave.cave[i].push_back(false);
        } else {
          updatedCave.cave[i].push_back(true);
        }
      } else {
        if (numOfNeighbors > birhtLimit) {
          updatedCave.cave[i].push_back(true);
        } else {
          updatedCave.cave[i].push_back(false);
        }
      }
    }
  }
  cave = updatedCave;
}
int CaveGenerator::CountAliveNeighbors(const cave_t& cave, int x, int y) {
  int numOfAlive = 0;
  for (int i = -1; i <= 1; ++i) {
    if (y + i < 0 || y + i >= cave.cols) {
      numOfAlive++;
      continue;
    }
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      if (x + j < 0 || x + j >= cave.rows) {
        numOfAlive++;
        continue;
      }
      if (cave.cave[y + i][x + j]) {
        numOfAlive++;
      }
    }
  }

  return numOfAlive;
}

void CaveGenerator::AllocateCave() {
  for (int i = 0; i < y_; i++) {
    cave_.cave.push_back(std::vector<bool>());
  }
}

void CaveGenerator::AllocateCave(cave_t& cave) {
  for (int i = 0; i < cave.cols; i++) {
    cave.cave.push_back(std::vector<bool>());
  }
}
