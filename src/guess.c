#pragma once

#include <stdbool.h>

typedef enum RelativeGuess {
    RELATIVE_CORRECT,
    RELATIVE_HIGHER,
    RELATIVE_LOWER
} RelativeGuess;

typedef struct GuessResult {
    bool primaryColourCorrect;
    bool secondaryColourCorrect;

    RelativeGuess difficulty;
    RelativeGuess length;
    RelativeGuess downloads;
    RelativeGuess likes;
    RelativeGuess objectCount;
} GuessResult;

bool GuessResult_IsCorrect(GuessResult guess) {
    return guess.primaryColourCorrect &&
           guess.secondaryColourCorrect &&
           guess.difficulty == RELATIVE_CORRECT &&
           guess.length == RELATIVE_CORRECT &&
           guess.downloads == RELATIVE_CORRECT &&
           guess.likes == RELATIVE_CORRECT &&
           guess.objectCount == RELATIVE_CORRECT;
}