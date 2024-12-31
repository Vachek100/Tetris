#include "score.h"

int score = 0;
int highScore = 0;


void loadHighScore() {
    FILE *file = fopen("score.txt", "r");
    if (file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
}

void saveHighScore(int score) {
    FILE *file = fopen("score.txt", "w");
    if (file) {
        fprintf(file, "%d", score);
        fclose(file);
    }
}
