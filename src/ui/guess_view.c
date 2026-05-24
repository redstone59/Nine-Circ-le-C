#pragma once

#include "../../lib/clay/clay.h"
#include <raylib.h>

#include "../logic/level.c"
#include "../logic/guess.c"

#include "level_thumbnails.c"

typedef struct GuessResultView {
    Level* level;
    GuessResult* result;
    Texture thumbnail;
} GuessResultView;

void GuessResultView_SetThumbnail(GuessResultView* view) {
    view->thumbnail = GetLevelThumbnail(view->level->id);
}

void GuessResultView_Initialise(GuessResultView* view, Level level, GuessResult result) {
    view->level = &level;
    view->result = &result;
    GuessResultView_SetThumbnail(view);
}

typedef struct GuessArray {
    GuessResultView* elements;
    size_t count;
    size_t capacity;
} GuessArray;

void GuessArray__Resize(GuessArray* arr) {
    size_t newCapacity = arr->capacity << 1;

    arr->elements = realloc(arr->elements, newCapacity);
    arr->capacity = newCapacity;
}

void GuessArray_Initialise(GuessArray* arr, size_t capacity) {
    if (arr->elements != NULL) {
        return;
    }
    
    arr->elements = malloc(capacity * sizeof(GuessResultView));
    arr->count = 0;
    arr->capacity = capacity;
}

void GuessArray_Free(GuessArray* arr) {
    if (arr->elements == NULL) {
        return;
    }

    free(arr->elements);
    arr->count = 0;
    arr->capacity = 0;
}

void GuessArray_Append(GuessArray* arr, GuessResultView view) {
    if (arr->count + 1 >= arr->capacity) {
        GuessArray__Resize(arr);
    }

    arr->elements[arr->count++] = view;
}

void RenderRelativeGuesses(GuessResult* result) {

}

void RenderColourGuesses(GuessResult* result) {

}

void RenderLevelInformation(GuessResultView* view) {
    Texture thumbnail = GetLevelThumbnail(view->level->id);

    CLAY_AUTO_ID({
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        }
    }) {
        CLAY_AUTO_ID({
            .image = {
                .imageData = &view->thumbnail
            }
        }) {}
    }
}

void RenderGuessResult(GuessResultView* view) {
    CLAY_AUTO_ID({
        .backgroundColor = {0, 0, 0, 255},
        .cornerRadius = CLAY_CORNER_RADIUS(8),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_FIT()
            },
            .layoutDirection = CLAY_LEFT_TO_RIGHT
        }
    }) {
        RenderLevelInformation(view);
        RenderColourGuesses(view->result);
        RenderRelativeGuesses(view->result);
    }
}