#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include "sdl_utils.h"
#include "events.h"
#include "score.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern int board[BOARD_HEIGHT][BOARD_WIDTH];
extern SDL_Color boardColors[BOARD_HEIGHT][BOARD_WIDTH];
extern bool fastFall;

bool checkCollision(Tetromino *tetromino);
void mergeTetromino(Tetromino *tetromino);
void clearLines();
void spawnTetromino();
void updateGame();

#endif // GAME_H