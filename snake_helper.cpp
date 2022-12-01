/** Contains helper functions for the snake game.
@file snake_helper.cpp
@author Miles Sharpton */

#include "snake_helper.h"

#include <iostream>
#include <set>
#include <vector>

#include "lib/snake.h"
using namespace std;

void draw_walls(char board[HEIGHT + 2][WIDTH + 2]) {
  for (int i = 0; i < HEIGHT + 2; i++) {
    board[i][0] = '#';
    board[i][WIDTH + 1] = '#';
  }
  for (int j = 0; j < WIDTH + 2; j++) {
    board[0][j] = '#';
    board[HEIGHT + 1][j] = '#';
  }
  return;
}

void draw_snake(char board[HEIGHT + 2][WIDTH + 2],
                const std::vector<Pos> snake) {
  if (snake.empty()) {
    return;
  }
  Pos head = snake[0];
  board[head.y][head.x] = '@';
  for (uint i = 1; i < snake.size(); i++) {
    Pos body = snake[i];
    board[body.y][body.x] = 'O';
  }
  return;
}

void draw_food(char board[HEIGHT + 2][WIDTH + 2], const std::set<Pos> food) {
  for (auto row = food.begin(); row != food.end(); row++) {
    Pos hungry = *row;
    board[hungry.y][hungry.x] = '+';
  }

  return;
}

bool collide_walls(const vector<Pos> snake, Move move) {
  if (snake.empty()) {
    return false;
  }
  Pos headcollide = snake.at(0);
  if (move == LEFT) {
    headcollide.x = headcollide.x - 1;
  }
  if (move == RIGHT) {
    headcollide.x = headcollide.x + 1;
  }
  if (move == DOWN) {
    headcollide.y = headcollide.y + 1;
  }

  if (move == UP) {
    headcollide.y = headcollide.y - 1;
  }

  if ((headcollide.y > 0) && (headcollide.y <= HEIGHT)) {
    if ((headcollide.x > 0) && (headcollide.x <= WIDTH)) {
      return false;
    }
  }
  return true;
}

bool collide_snake(const vector<Pos> snake, Move move) {
  if (snake.empty()) {
    return false;
  }
  Pos headcollide = snake.at(0);
  if (move == LEFT) {
    headcollide.x = headcollide.x - 1;
  }
  if (move == RIGHT) {
    headcollide.x = headcollide.x + 1;
  }
  if (move == DOWN) {
    headcollide.y = headcollide.y + 1;
  }

  if (move == UP) {
    headcollide.y = headcollide.y - 1;
  }
  for (uint i = 1; i < snake.size(); i++) {
    if (headcollide == snake[i - 1]) {
      return true;
    }
  }
  return false;
}

bool collide_food(const vector<Pos> snake, Move move, const set<Pos> food) {
  if (snake.empty()) {
    return false;
  }
  Pos headcollide = snake.at(0);
  if (move == LEFT) {
    headcollide.x = headcollide.x - 1;
  }
  if (move == RIGHT) {
    headcollide.x = headcollide.x + 1;
  }
  if (move == DOWN) {
    headcollide.y = headcollide.y + 1;
  }

  if (move == UP) {
    headcollide.y = headcollide.y - 1;
  }
  for (auto it = food.begin(); it != food.end(); it++) {
    if (headcollide == *it) {
      return true;
    }
  }
  return false;
}