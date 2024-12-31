#include "game.h"


int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
SDL_Color boardColors[BOARD_HEIGHT][BOARD_WIDTH] = {0};
bool fastFall = false;

bool checkCollision(Tetromino *tetromino) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (tetromino->shape[y][x]) {
                int newX = tetromino->x + x;
                int newY = tetromino->y + y;
                if (newX < 0 || newX >= BOARD_WIDTH || newY >= BOARD_HEIGHT || (newY >= 0 && board[newY][newX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mergeTetromino(Tetromino *tetromino) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (tetromino->shape[y][x]) {
                board[tetromino->y + y][tetromino->x + x] = 1;
                boardColors[tetromino->y + y][tetromino->x + x] = tetromino->color;
            }
        }
    }
}

void clearLines() {
    int linesCleared = 0;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        bool fullLine = true;
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (!board[y][x]) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            linesCleared++;
            for (int yy = y; yy > 0; yy--) {
                for (int xx = 0; xx < BOARD_WIDTH; xx++) {
                    board[yy][xx] = board[yy - 1][xx];
                    boardColors[yy][xx] = boardColors[yy - 1][xx];
                }
            }
            for (int xx = 0; xx < BOARD_WIDTH; xx++) {
                board[0][xx] = 0;
                boardColors[0][xx] = (SDL_Color){0, 0, 0, 0};
            }
        }
    }
    score += linesCleared;
}

void spawnTetromino() {
    currentTetromino = nextTetromino;
    nextTetromino.x = BOARD_WIDTH / 2 - 2;
    nextTetromino.y = 0;
    int shapeIndex = rand() % 7;
    memcpy(nextTetromino.shape, tetrominoShapes[shapeIndex], sizeof(nextTetromino.shape));
    nextTetromino.color = predefinedColors[rand() % (sizeof(predefinedColors) / sizeof(predefinedColors[0]))];
    if (checkCollision(&currentTetromino)) {
        running = false; // Game over
    }
}

void updateGame() {
    static Uint32 lastMoveTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    Uint32 fallInterval = fastFall ? 50 : 500; // Faster fall when DOWN key is pressed
    if (currentTime - lastMoveTime > fallInterval) {
        Tetromino temp = currentTetromino;
        temp.y++;
        if (!checkCollision(&temp)) {
            currentTetromino.y++;
        } else {
            mergeTetromino(&currentTetromino);
            clearLines();
            spawnTetromino();
        }
        lastMoveTime = currentTime;
    }
}
