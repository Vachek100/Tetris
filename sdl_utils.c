#include "sdl_utils.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *blockTexture = NULL;
SDL_Texture *backgroundTexture = NULL;
TTF_Font *font = NULL;
Mix_Music *backgroundMusic = NULL;


void initSDL() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
    if (TTF_Init() == -1) {
        printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_WEBP) & (IMG_INIT_PNG | IMG_INIT_WEBP))) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        exit(1);
    }
    blockTexture = IMG_LoadTexture(renderer, "tetromino_block.png");
    if (!blockTexture) {
        printf("Failed to load texture: %s\n", IMG_GetError());
        exit(1);
    }
    backgroundTexture = IMG_LoadTexture(renderer, "background.webp");
    if (!backgroundTexture) {
        printf("Failed to load background texture: %s\n", IMG_GetError());
        exit(1);
    }
    font = TTF_OpenFont("arcade.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit(1);
    }
    backgroundMusic = Mix_LoadMUS("music.flac");
    if (!backgroundMusic) {
        printf("Failed to load background music: %s\n", Mix_GetError());
        exit(1);
    }
    Mix_PlayMusic(backgroundMusic, -1); // Play music in a loop
}

void cleanupSDL() {
    Mix_FreeMusic(backgroundMusic);
    TTF_CloseFont(font);
    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

