#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#define BLOCK_SIZE 30 // Increased block size
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define SCREEN_WIDTH (BOARD_WIDTH * BLOCK_SIZE + 150) // Extra space for next piece preview
#define SCREEN_HEIGHT (BOARD_HEIGHT * BLOCK_SIZE)
#define FPS 60

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *blockTexture;
extern SDL_Texture *backgroundTexture;
extern TTF_Font *font;
extern Mix_Music *backgroundMusic;

void initSDL();
void cleanupSDL();

#endif // SDL_UTILS_H