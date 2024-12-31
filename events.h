#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include "tetromino.h"
#include "sdl_utils.h"
#include "game.h"
#include <stdbool.h>

extern bool running;
extern bool gameStarted;

void handleEvents();

#endif // EVENTS_H