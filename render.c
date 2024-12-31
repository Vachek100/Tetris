#include "render.h"



void renderText(const char *text, int x, int y, int fontSize) {
    TTF_Font *tempFont = TTF_OpenFont("arcade.ttf", fontSize);
    SDL_Color color = {255, 255, 255, 255}; // White color
    SDL_Surface *surface = TTF_RenderText_Solid(tempFont, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(tempFont);
}

void renderForeshadowing(Tetromino *tetromino) {
    Tetromino shadow = *tetromino;
    while (!checkCollision(&shadow)) {
        shadow.y++;
    }
    shadow.y--;
    SDL_SetRenderDrawColor(renderer, shadow.color.r, shadow.color.g, shadow.color.b, 255);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shadow.shape[y][x]) {
                SDL_Rect rect = {(shadow.x + x) * BLOCK_SIZE, (shadow.y + y) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

void renderGame() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Draw grid
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    for (int y = 0; y <= BOARD_HEIGHT; y++) {
        SDL_RenderDrawLine(renderer, 0, y * BLOCK_SIZE, BOARD_WIDTH * BLOCK_SIZE, y * BLOCK_SIZE);
    }
    for (int x = 0; x <= BOARD_WIDTH; x++) {
        SDL_RenderDrawLine(renderer, x * BLOCK_SIZE, 0, x * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE);
    }

    // Draw board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[y][x]) {
                SDL_SetTextureColorMod(blockTexture, boardColors[y][x].r, boardColors[y][x].g, boardColors[y][x].b);
                SDL_Rect rect = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                SDL_RenderCopy(renderer, blockTexture, NULL, &rect);
            }
        }
    }

    // Draw foreshadowing
    renderForeshadowing(&currentTetromino);

    // Draw current tetromino
    SDL_SetTextureColorMod(blockTexture, currentTetromino.color.r, currentTetromino.color.g, currentTetromino.color.b);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentTetromino.shape[y][x]) {
                SDL_Rect rect = {(currentTetromino.x + x) * BLOCK_SIZE, (currentTetromino.y + y) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                SDL_RenderCopy(renderer, blockTexture, NULL, &rect);
            }
        }
    }

    // Draw score
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    renderText(scoreText, BOARD_WIDTH * BLOCK_SIZE + 10, 10, 12);

    // Draw next tetromino
    renderText("Next Piece", BOARD_WIDTH * BLOCK_SIZE + 10, 40, 12);
    SDL_SetTextureColorMod(blockTexture, nextTetromino.color.r, nextTetromino.color.g, nextTetromino.color.b);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (nextTetromino.shape[y][x]) {
                SDL_Rect rect = {(BOARD_WIDTH * BLOCK_SIZE) + (x * BLOCK_SIZE) + 10, (y * BLOCK_SIZE) + 70, BLOCK_SIZE, BLOCK_SIZE};
                SDL_RenderCopy(renderer, blockTexture, NULL, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void renderMenu() {
    SDL_RenderClear(renderer);

    // Draw background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    renderText("Tetris", SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 - 100, 36);
    renderText("by Vaclav Kralik", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 18);
          // Draw start button text     
    renderText("Start Game", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 60, 24);      
    renderText("github.com/Vachek100", SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT - 25, 12);

    // Draw high score
    char highScoreText[30];
    sprintf(highScoreText, "High Score: %d", highScore);
    renderText(highScoreText, SCREEN_WIDTH / 2 - 110, 30, 18);

    SDL_RenderPresent(renderer);
}
