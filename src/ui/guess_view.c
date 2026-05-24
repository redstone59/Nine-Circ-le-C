#pragma once

#include "../../lib/clay/clay.h"
#include <raylib.h>

#include "../logic/level.c"
#include "../logic/guess.c"

#include "level_thumbnails.c"

void RenderRelativeGuesses(GuessResult* result) {

}

void RenderColourGuesses(GuessResult* result) {

}

void RenderLevelInformation(Level* level) {
    Texture2D thumbnail = GetLevelThumbnail(level->id);
}

void RenderGuessResult(Level* level, GuessResult* result) {
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
        RenderLevelInformation(level);
        RenderColourGuesses(result);
        RenderRelativeGuesses(result);
    }
}