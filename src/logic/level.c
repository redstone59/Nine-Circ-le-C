#pragma once

#include "../../lib/clay/clay.h"

typedef enum Colour {
    NC_COLOR_RED,
    NC_COLOR_PINK,
    NC_COLOR_ORANGE,
    NC_COLOR_BROWN,
    NC_COLOR_YELLOW,
    NC_COLOR_GREEN,
    NC_COLOR_BLUE,
    NC_COLOR_INDIGO,
    NC_COLOR_VIOLET,
    NC_COLOR_CYAN,
    NC_COLOR_MAGENTA,
    NC_COLOR_PURPLE,
    NC_COLOR_BLACK,
    NC_COLOR_GREY,
    NC_COLOR_WHITE,
    NC_COLOR_MULTICOLOUR,
    NC_COLOR_PLAYER_COLOUR_1,
    NC_COLOR_PLAYER_COLOUR_2,
} Colour;

typedef enum Difficulty {
    NC_DIFF_AUTO,
    NC_DIFF_EASY,
    NC_DIFF_NORMAL,
    NC_DIFF_HARD,
    NC_DIFF_HARDER,
    NC_DIFF_INSANE,
    NC_DIFF_EASY_DEMON,
    NC_DIFF_MEDIUM_DEMON,
    NC_DIFF_HARD_DEMON,
    NC_DIFF_INSANE_DEMON,
    NC_DIFF_EXTREME_DEMON
} Difficulty;

typedef enum Length {
    NC_LENGTH_SHORT,
    NC_LENGTH_MEDIUM,
    NC_LENGTH_LONG,
    NC_LENGTH_XL,
    NC_LENGTH_PLATFORMER
} Length;

typedef enum Rating {
    NC_RATING_RATE,
    NC_RATING_FEATURE,
    NC_RATING_EPIC,
    NC_RATING_LEGENDARY,
    NC_RATING_MYTHIC
} Rating;

typedef struct Level {
    // API Information

    uint32_t id;
    Clay_String name;
    Clay_String description;
    Difficulty difficulty;
    uint8_t stars;
    Length length;
    uint64_t downloads;
    uint64_t likes;
    uint64_t objectCount;
    Rating rating;

    // Non-API information (from wiki)

    Colour primaryColour;
    Colour secondaryColour;

    Clay_String* creators;
    size_t creatorCount;
    Clay_String verifier;
} Level;

typedef struct LevelArray {
    Level* elements;
    size_t count;
} LevelArray;