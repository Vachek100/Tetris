#ifndef RENDER_H
#define RENDER_H

#include "sdl_utils.h"
#include "tetromino.h"
#include "score.h"
#include "game.h"


void renderText(const char *text, int x, int y, int fontSize);
void renderForeshadowing(Tetromino *tetromino);
void renderGame();
void renderMenu();

#endif // RENDER_H
