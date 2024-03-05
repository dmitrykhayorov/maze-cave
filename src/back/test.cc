
#include <gtest/gtest.h>

#include "../back/mazegenerator.h"
#include "parser.h"

using namespace s21;

TEST(test_input, no_file) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("non-existing_file"));
}

TEST(test_input, empty_file) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/empty_file.txt"));
}

TEST(test_input, wrong_file_content_1) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/wrong_maze_1.txt"));
}

TEST(test_input, wrong_file_content_2) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/wrong_maze_2.txt"));
}

TEST(test_input, wrong_file_content_3) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/wrong_maze_3.txt"));
}

TEST(test_input, wrong_file_content_4) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/wrong_maze_4.txt"));
}

TEST(test_input, wrong_file_content_5) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/wrong_maze_5.txt"));
}

TEST(test_input, wrong_file_content_6) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/wrong_maze_6.txt"));
}

TEST(test_input, wrong_file_content_7) {
  Parser buf;
  EXPECT_ANY_THROW(buf.SetFilepathMaze("examples_wrong/wrong_maze_7.txt"));
}

TEST(test_input, normal_file_1) {
  Parser buf;
  buf.SetFilepathMaze("examples/maze_1.txt");
  maze_t result = buf.GetVectorsMaze();

  EXPECT_EQ(result.mazeRightBorder[0][0], 1);
  EXPECT_EQ(result.mazeRightBorder[0][1], 0);
  EXPECT_EQ(result.mazeRightBorder[1][0], 0);
  EXPECT_EQ(result.mazeRightBorder[1][1], 1);

  EXPECT_EQ(result.mazeBottomBorder[0][0], 0);
  EXPECT_EQ(result.mazeBottomBorder[0][1], 1);
  EXPECT_EQ(result.mazeBottomBorder[1][0], 1);
  EXPECT_EQ(result.mazeBottomBorder[1][1], 0);
}

TEST(test_generator_maze, invalid_input_1) {
  mazeGenerator m;
  EXPECT_ANY_THROW(m.GeneratePerfectMaze(0));
}

TEST(test_generator_maze, invalid_input_2) {
  mazeGenerator m;
  EXPECT_ANY_THROW(m.GeneratePerfectMaze(51));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}