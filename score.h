#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>

extern int score;
extern int highScore;

void loadHighScore();
void saveHighScore(int score);

#endif // SCORE_H