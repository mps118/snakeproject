/** Contains tests for your code.
@file snake_helper_test.cpp
@author Miles Sharpton */

#include "snake_helper.h"

#include <gtest/gtest.h>

#include "lib/snake.h"
using namespace std;

void init_board(char board[HEIGHT + 2][WIDTH + 2]);
void EXPECT_BOARD(char board[HEIGHT + 2][WIDTH + 2], const string& image);

TEST(DrawWalls, Test1) {
  char board[HEIGHT + 2][WIDTH + 2];
  init_board(board);

  draw_walls(board);
  string expected = R"(
    ######################
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    ######################
  )";
  EXPECT_BOARD(board, expected);
}

// DO NOT MODIFY ANYTHING BEFORE THIS LINE

TEST(DrawSnake, Test1) {
  char board[HEIGHT + 2][WIDTH + 2];
  init_board(board);
  vector<Pos> snake = {{.x = 7, .y = 5}, {.x = 7, .y = 6}, {.x = 7, .y = 7}};

  draw_walls(board);
  draw_snake(board, snake);
  string expected = R"(
    ######################
    #                    #
    #                    #
    #                    #
    #                    #
    #      @             #
    #      O             #
    #      O             #
    #                    #
    #                    #
    #                    #
    ######################
  )";
  EXPECT_BOARD(board, expected);
}
TEST(DrawSnake, Test2) {
  char board[HEIGHT + 2][WIDTH + 2];
  init_board(board);
  vector<Pos> snake = {{.x = 1, .y = 2}, {.x = 2, .y = 2}, {.x = 3, .y = 2}};

  draw_walls(board);
  draw_snake(board, snake);
  string expected = R"(
    ######################
    #                    #
    #@OO                 #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    ######################
  )";
  EXPECT_BOARD(board, expected);
}
TEST(DrawSnake, Test3) {
  char board[HEIGHT + 2][WIDTH + 2];
  init_board(board);
  vector<Pos> snake = {{.x = 1, .y = 2}, {.x = 1, .y = 2}, {.x = 1, .y = 2}};

  draw_walls(board);
  draw_snake(board, snake);
  string expected = R"(
    ######################
    #                    #
    #@                   #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    ######################
  )";
  EXPECT_BOARD(board, expected);
}

TEST(DrawFood, Test1) {
  char board[HEIGHT + 2][WIDTH + 2];
  init_board(board);
  set<Pos> food = {{.x = 3, .y = 5}, {.x = 12, .y = 9}, {.x = 16, .y = 10}};

  draw_walls(board);
  draw_food(board, food);
  string expected = R"(
    ######################
    #                    #
    #                    #
    #                    #
    #                    #
    #  +                 #
    #                    #
    #                    #
    #                    #
    #           +        #
    #               +    #
    ######################
  )";
  EXPECT_BOARD(board, expected);
}

TEST(DrawFood, Test2) {
  char board[HEIGHT + 2][WIDTH + 2];
  init_board(board);
  set<Pos> food = {{.x = 2, .y = 2}, {.x = 7, .y = 5}, {.x = 16, .y = 3}};

  draw_walls(board);
  draw_food(board, food);
  string expected = R"(
    ######################
    #                    #
    # +                  #
    #               +    #
    #                    #
    #      +             #
    #                    #
    #                    #
    #                    #
    #                    #
    #                    #
    ######################
  )";
  EXPECT_BOARD(board, expected);
}

TEST(CollideWalls, Test1) {
  vector<Pos> snake = {{.x = 1, .y = 10}, {.x = 2, .y = 10}, {.x = 3, .y = 10}};
  Move move = LEFT;

  bool expected = true;
  EXPECT_EQ(collide_walls(snake, move), expected);
}
TEST(CollideWalls, Test2) {
  vector<Pos> snake = {{.x = 8, .y = 1}, {.x = 8, .y = 2}, {.x = 8, .y = 3}};
  Move move = UP;
  bool expected = true;
  EXPECT_EQ(collide_walls(snake, move), expected);
}
TEST(CollideWalls, Test3) {
  vector<Pos> snake = {{.x = 8, .y = 5}, {.x = 8, .y = 6}, {.x = 8, .y = 7}};
  Move move = UP;

  bool expected = false;
  EXPECT_EQ(collide_walls(snake, move), expected);
}
TEST(CollideSnake, Test1) {
  vector<Pos> snake = {{.x = 5, .y = 3}, {.x = 6, .y = 3}, {.x = 6, .y = 2}};
  Move move = RIGHT;

  bool expected = true;
  EXPECT_EQ(collide_snake(snake, move), expected);
}
TEST(CollideSnake, Test2) {
  vector<Pos> snake = {{.x = 6, .y = 3}, {.x = 5, .y = 3}, {.x = 5, .y = 2}};
  Move move = DOWN;

  bool expected = false;
  EXPECT_EQ(collide_snake(snake, move), expected);
}

TEST(CollideFood, Test1) {
  vector<Pos> snake = {{.x = 7, .y = 5}, {.x = 7, .y = 4}, {.x = 7, .y = 3}};
  Move move = UP;
  set<Pos> food = {{.x = 8, .y = 2}, {.x = 1, .y = 5}, {.x = 9, .y = 9}};

  bool expected = false;
  EXPECT_EQ(collide_food(snake, move, food), expected);
}
// DO NOT MODIFY ANYTHING BEYOND THIS LINE

void init_board(char board[HEIGHT + 2][WIDTH + 2]) {
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      board[i][j] = ' ';
    }
  }
}

void fill_board(char board[HEIGHT + 2][WIDTH + 2], const string& image) {
  deque<deque<char>> d = {{}};
  for (char c : image) {
    if (c == '\n') {
      d.push_back({});
    } else if (!d.back().empty() || c != ' ') {
      d.back().push_back(c);
    }
  }
  while (d.front().empty()) {
    d.pop_front();
  }
  int i = 0;
  for (const deque<char>& row : d) {
    if (i >= HEIGHT + 2) {
      break;
    }
    int j = 0;
    for (char c : row) {
      if (j >= WIDTH + 2) {
        break;
      }
      board[i][j] = c;
      j++;
    }
    i++;
  }
}

string to_image(char board[HEIGHT + 2][WIDTH + 2]) {
  string out = "";
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      out += board[i][j];
    }
    out += '\n';
  }
  return out;
}

void EXPECT_BOARD(char board[HEIGHT + 2][WIDTH + 2], const string& image) {
  char expected[HEIGHT + 2][WIDTH + 2];
  fill_board(expected, image);
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      ASSERT_EQ(board[i][j], expected[i][j])
          << "expected:\n"
          << to_image(expected) << "\nactual:\n"
          << to_image(board) << "\n";
    }
  }
}