#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL2/SDL.h>

typedef struct {
    int shape[4][4];
    SDL_Color color;
    int x, y;
} Tetromino;

extern Tetromino currentTetromino;
extern Tetromino nextTetromino;

extern int tetrominoShapes[7][4][4];
extern SDL_Color predefinedColors[9];

#endif // TETROMINO_H