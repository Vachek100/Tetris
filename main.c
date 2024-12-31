#include "tetromino.h"
#include "sdl_utils.h"
#include "game.h"
#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include "events.h"
#include "render.h"
#include <time.h>

int main() {
    srand(time(NULL));
    initSDL();
    loadHighScore();
    nextTetromino.x = BOARD_WIDTH / 2 - 2;
    nextTetromino.y = 0;
    int shapeIndex = rand() % 7;
    memcpy(nextTetromino.shape, tetrominoShapes[shapeIndex], sizeof(nextTetromino.shape));
    nextTetromino.color = predefinedColors[rand() % (sizeof(predefinedColors) / sizeof(predefinedColors[0]))];
    spawnTetromino();

    Uint32 startTime;
    while (running) {
        startTime = SDL_GetTicks();

        handleEvents();
        if (gameStarted) {
            updateGame();
            renderGame();
        } else {
            renderMenu();
        }

        Uint32 frameTime = SDL_GetTicks() - startTime;
        if (frameTime < 1000 / FPS) {
            SDL_Delay(1000 / FPS - frameTime);
        }
    }

    if (score > highScore) {
        saveHighScore(score);
    }


    //cleanupSDL();   
    return 0;
}