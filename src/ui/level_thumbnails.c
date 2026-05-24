#pragma once

#include <raylib.h>
#include <stdint.h>

#include "../string_builder.c"

Texture2D GetLevelThumbnail(uint64_t id) {
    StringBuilder urlBuilder = {0};
    StringBuilder_Initialise(&urlBuilder, 64);

    const char* thumbnailRoot = "https://levelthumbs.prevter.me/thumbnail/";
    // strlen is bad right isn't it
    StringBuilder_Append(&urlBuilder, thumbnailRoot, strlen(thumbnailRoot));

    char idString[64];
    sprintf(idString, "%d", id);
    StringBuilder_Append(&urlBuilder, idString, strlen(idString));

    StringBuilder_Terminate(&urlBuilder);
    Texture2D thumbnail = LoadTexture(urlBuilder.chars);
    StringBuilder_Free(&urlBuilder);

    return thumbnail;
}