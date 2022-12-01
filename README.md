# Project 2.1: Snake

In this project, you will learn how to:
* use 2D arrays
* use enums
* use structs
* use vectors
* use sets

### File structure

* `Makefile` - Configuration for `make`.
* `snake_helper.cpp` - Your code goes here.
* `snake_helper_test.cpp` - Your tests go here.
* `snake_helper.h` - Header file for `snake_helper.cpp`, already written for you.
* `LICENSE` - Legal boilerplate stuff.
* `googletest/` - Contains code for the GoogleTest framework.
* `lib/` - Contains library files you may reference.
    * `snake_main.cpp` - Contains main function which runs the snake game.
    * `snake_logic.cpp` - Contains functions that implement the game logic.
    * `snake_logic.h` - Header file for `snake_logic.cpp`.
    * `snake.h` - Contains enum & struct definitions relevant to the snake game.

**Do not change any files other than `snake_helper.cpp` and `snake_helper_test.cpp`!**

## Make commands

You have the same `make` commands as usual (format, test, build, all, clean). **Don't use g++**.

## The Snake game

Try it yourself [here](https://g.co/kgs/PxJqP6)!

Or, run the completed program in your console by typing `./snake_complete`. It will ask you to "enter 1 for real-time snake, 0 for turn-based snake." Real-time snake means playing with real-time keyboard inputs (WASD or arrow keys). Turn-based snake is useful for debugging purposes and takes in commands one at a time (WASD followed by Enter).

Rules:

1. You are a snake moving on a 2D board.
1. At the beginning, your body is 3 cases long (but you're squished into 1 case).
1. You start at a random valid position. Each turn, you can either move up, down, left or right.
1. You start with 100 health. Each turn, you lose 1 health.
1. Food will spawn randomly on the board. You grow by 1 and reset your health to 100 by eating food.
1. You die if you go out of bounds.
1. You die if you collide with a snake (that includes yourself).
1. The goal is to survive as long as possible.

Example screenshot:

```
######################
#                    #
# +                  #
#                 +  #
# +     @            #
#      +O            #
# +     OO           #
#      OOO           #
#      O             #
#      O          ++ #
#     +              #
######################
Snake - WASD (C)ontinue (R)estart (Q)uit - Turn: 55
ID: player - HP: 100 - Length: 9
```
* \#: wall
* @: snake head
* O: snake body
* +: food

You will be implementing and testing a series of functions to draw the board and to detect collisions. Everything else has already been written for you. If you're curious, take at look at the files in `lib/`.

**You don't need to worry about invalid inputs. Autograder tests will derive from situations that could happen in the actual game.**

#### Drawing the board

1. `draw_walls()` - Given a 2D array that represents the board, draws the border walls using '#'. 
1. `draw_snake()` - Given a snake and a 2D array that represents the board, draws the snake head using '@' and the snake body using 'O'.
1. `draw_food()` - Given a set of food locations and a 2D array that represents the board, draws every piece of food using '+'.

Without your drawing functions, the game might still be running, but none of the above symbols will be printed to the screen.

#### Collision detection

1. `collide_walls()` - Given a snake and a pending move, returns whether the snake will collide with walls if the move is executed.
1. `collide_snake()` - Given a snake and a pending move, returns whether the snake will collide with itself if the move is executed.
1. `collide_food()` - Given a snake, a pending move and a set of food positions, returns whether the snake will collide with any food if the move is executed.

Without collision detection, your snake will always die from hunger since they will never be able to eat (collide with) food, nor die from other means. Run `./snake_no_collide` to experience how that'd feel like.

### Data structures

Here are the relevant data structures for this project.

#### Board

```c++
char board[HEIGHT + 2][WIDTH + 2];
```

`HEIGHT` and `WIDTH` are constants defined in `lib/snake.h`. They specify the total area the snake can move in. The char array is declared with `+2` to each dimension because we want to surround the play space with border walls ('#'s). By default, the board is filled with white spaces (' ' characters). The snake head should be represented using '@', the snake body 'O', and food '+'.

#### Pos

```c++
struct Pos {
  int x;
  int y;
};
```

A Pos represents a position on the board. `x` specifies the column from left to right, `y` specifies the row from top to bottom. Here's what each position (x, y) would look like on a board with `HEIGHT` 3 and `WIDTH` 2.

```
|--------|--------|--------|--------|
| (0, 0) | (1, 0) | (2, 0) | (3, 0) |
|--------|--------|--------|--------|
| (0, 1) | (1, 1) | (2, 1) | (3, 1) |
|--------|--------|--------|--------|
| (0, 2) | (1, 2) | (2, 2) | (3, 2) |
|--------|--------|--------|--------|
| (0, 3) | (1, 3) | (2, 3) | (3, 3) |
|--------|--------|--------|--------|
| (0, 4) | (1, 4) | (2, 4) | (3, 4) |
|--------|--------|--------|--------|
```

This means that, combined with the above, any position with `x = 0`, `x = 3`, `y = 0` or `y = 4` should be represented with a '#' on the board.

#### Move

```c++
enum Move {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NONE,
};
```

Move represents the direction that the snake will go towards next. It shouldn't ever be `NONE` unless we're in an error state. User input is handled in `lib/snake_main.cpp` and translated to one of `UP`, `DOWN`, `LEFT` or `RIGHT`.

#### Snake

```c++
vector<Pos> snake;
```

A snake is represented by a vector of Pos. The first element is the position of the head, the rest represents the body, in order. There shouldn't be any duplicate positions except at the beginning where the snake is all squished together at a random valid position.

Eg. At the beginning of the game, the snake is randomly spawned at position (2, 0):
```
snake = {{.x = 2, .y = 0}, {.x = 2, .y = 0}, {.x = 2, .y = 0}};
```
After moving `DOWN`:
```
snake = {{.x = 2, .y = 1}, {.x = 2, .y = 0}, {.x = 2, .y = 0}};
```
After moving `LEFT`:
```
snake = {{.x = 1, .y = 1}, {.x = 2, .y = 1}, {.x = 2, .y = 0}};
```
After moving `DOWN`:
```
snake = {{.x = 1, .y = 2}, {.x = 1, .y = 1}, {.x = 2, .y = 1}};
```
After moving `DOWN` and colliding with food:
```
snake = {{.x = 1, .y = 3}, {.x = 1, .y = 2}, {.x = 1, .y = 1}, {.x = 2, .y = 1}};
```

#### Food

```c++
set<Pos> food;
```

Food is represented by a set of Pos. The ordering doesn't matter.

Eg. This means there's food at position (2, 0) and (1, 4) on the board.
```
food = {{.x = 2, .y = 0}, {.x = 1, .y = 4}};
```

## Part 1: array functions

#### `void draw_walls(char board[HEIGHT + 2][WIDTH + 2]);`

Given the board which is a 2D char array passed by reference, modify it to include walls ('#'). The test case has already been written for you in `snake_helper_test.cpp`.

```c++
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
```

For this test case, `init_board(board)` fills `board` with white spaces (' ' character). Then, it's passed to your `draw_walls()` function and we expect it to come out with walls ('#'). `EXPECT_BOARD` does some *magic* to convert the multiline string `expected` into a 2D char array that can be compared to `board`.

**Complete the implementation in `snake_helper.cpp` and make sure the above test case passes when you run `make test`.**

## Part 2: vector functions

#### `void draw_snake(char board[HEIGHT + 2][WIDTH + 2], const std::vector<Pos> snake);`

Given the board which is a 2D char array passed by reference, and the snake which is a constant vector of Pos, modify the board to include the snake ('@' for the head and 'O' for the body).

Complete the `TEST(DrawSnake, Test1)` test case by coming up with a vector of Pos for the snake and modifying the expected board accordingly. Note that this assumes `draw_walls()` is implemented properly. Eg.

```
######################
#                    #
#                    #
#                    #
#                    #
#           OOO@     #
#           O        #
#         OOO        #
#                    #
#                    #
#                    #
######################
```

Duplicate the test case to make sure different scenarios are tested. Don't forget to rename subsequent tests. (Eg. Test2, Test3, etc.)

#### `bool collide_walls(const std::vector<Pos> snake, Move move);`

Given the snake which is a constant vector of Pos, and a pending move, determine whether the snake will collide with any walls after the move is applied.

For example, given the snake on the mini board below (`(3, 1)`, `(2, 1)`, `(2, 2)`), return `true` if the move is `UP` or `RIGHT` because the snake would run into a wall.

```
#####
# O@#
# O #
#####
```

Complete the `TEST(CollideWalls, Test1)` test case and duplicate it to cover different scenarios.

#### `bool collide_snake(const std::vector<Pos> snake, Move move);`

Given the snake which is a constant vector of Pos, and a pending move, determine whether the snake will collide with itself after the move is applied.

For example, given the snake on the mini board below (`(3, 1)`, `(2, 1)`, `(2, 2)`, `(3, 2)`), return `true` if the move is `LEFT` because the snake would run into itself. Be careful - it should return `false` if the move is `DOWN` because the snake tail would be out of the way after the move is applied.

```
#####
# O@#
# OO#
#####
```

Complete the `TEST(CollideSnake, Test1)` test case and duplicate it to cover different scenarios.

**Complete the implementation of the above functions in `snake_helper.cpp` and make sure your test cases pass when you run `make test`. Run the game after `make build` using `./snake`.**

## Part 3: set functions

#### `void draw_food(char board[HEIGHT + 2][WIDTH + 2], const std::set<Pos> food);`

Given the board which is a 2D char array passed by reference, and a constant set of Pos representing food locations, modify the board to include all the food ('+').

Complete the `TEST(DrawFood, Test1)` test case by coming up with a set of Pos for the food locations and modifying the expected board accordingly. Note that this assumes `draw_walls()` is implemented properly. Eg.

```
######################
#                    #
#                    #
#   +                #
#                    #
#            +       #
#                    #
#                    #
#                    #
#        +           #
#                    #
######################
```

Duplicate the test case to make sure different scenarios are tested. Don't forget to rename subsequent tests. (Eg. Test2, Test3, etc.)

#### `bool collide_food(const std::vector<Pos> snake, Move move, const std::set<Pos> food);`

Given the snake which is a constant vector of Pos, a pending move, and a constant set of Pos representing food locations, determine whether the snake will collide with any of the food in the set.

For example, given the snake (`(2, 1)`, `(1, 1)`, `(1, 2)`) and food locations (`(3, 2)`, `(3, 1)`) on the mini board below, return `true` if the move is `RIGHT` because the snake would run into the food at location `(3, 1)`.

```
#####
#O@+#
#O +#
#####
```

Complete the `TEST(CollideFood, Test1)` test case and duplicate it to cover different scenarios.

**Complete the implementation of the above functions in `snake_helper.cpp` and make sure your test cases pass when you run `make test`. Run the game after `make build` using `./snake`.**

## Rubric

* (75 points) Programming
  * (1 point) TODO comment check
  * (1 point) Style check
  * (53 points) Autograder test cases
    * (4 points) `draw_walls()`
    * (8 points) `draw_snake()`
    * (6 points) `draw_food()`
    * (4 points) all 3 functions above combined
    * (8 points) `collide_walls()`
    * (15 points) `collide_snake()`
    * (8 points) `collide_food()`
  * (20 points) Good test cases in `snake_helper_test.cpp`
