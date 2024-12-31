#include "events.h"

bool running = true;
bool gameStarted = false;

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            Tetromino temp = currentTetromino;
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    temp.x--;
                    if (!checkCollision(&temp)) {
                        currentTetromino.x--;
                    }
                    break;
                case SDLK_RIGHT:
                    temp.x++;
                    if (!checkCollision(&temp)) {
                        currentTetromino.x++;
                    }
                    break;
                case SDLK_DOWN:
                    fastFall = true;
                    break;
                case SDLK_UP:
                    // Rotate tetromino
                    for (int y = 0; y < 4; y++) {
                        for (int x = 0; x < 4; x++) {
                            temp.shape[y][x] = currentTetromino.shape[3 - x][y];
                        }
                    }
                    if (!checkCollision(&temp)) {
                        memcpy(currentTetromino.shape, temp.shape, sizeof(currentTetromino.shape));
                    }
                    break;
                case SDLK_RETURN:
                    if (!gameStarted) {
                        gameStarted = true;
                    }
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_DOWN) {
                fastFall = false;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= SCREEN_WIDTH / 2 - 50 && x <= SCREEN_WIDTH / 2 + 50 && y >= SCREEN_HEIGHT / 2 + 50 && y <= SCREEN_HEIGHT / 2 + 100) {
                gameStarted = true;
            }
        }
    }
}
