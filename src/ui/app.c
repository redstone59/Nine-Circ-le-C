#include "../../lib/clay/clay.h"
#include "../../lib/clay/renderers/raylib/clay_renderer_raylib.c"

#define ASSET(path) "./assets/" path

typedef enum Fonts {
    FONT_PUSAB,
    FONT_MAX
} Fonts;

typedef struct NineCircleAppImages {
    Texture nineCircleLogo;
    Texture youWin;
    
    Texture backgroundWidescreen;
    Texture vignetteWidescreen;
    Texture backgroundThin;
    Texture vignetteThin;
} NineCircleAppImages;

typedef struct NineCircleAppData {
    Font* fonts;
    Clay_Arena arena;

    NineCircleAppImages images;
} NineCircleAppData;

void NineCircleAppImages_Initialise(NineCircleAppImages* images) {
    images->nineCircleLogo = LoadTexture(ASSET("logo.png"));
    images->youWin = LoadTexture(ASSET("you win.png"));
    
    images->backgroundWidescreen = LoadTexture(ASSET("widescreen_background.png"));
    images->vignetteWidescreen = LoadTexture(ASSET("widescreen vignette.png"));
    images->backgroundThin = LoadTexture(ASSET("mobile background.png"));
    images->vignetteThin = LoadTexture(ASSET("vignette"));
}

void NineCircleAppData_Initialise(NineCircleAppData* data, Font* fonts, Clay_Arena arena) {
    data->fonts = fonts;
    data->arena = arena;
    NineCircleAppImages_Initialise(&data->images);
}

Clay_RenderCommandArray NineCircleApp_GetRenderCommands(NineCircleAppData* data) {
    Clay_BeginLayout();

    CLAY(
        CLAY_ID("root"), {
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            },
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
        .image = {
            .imageData = &(data->images.backgroundWidescreen)
        }
    }) {
        // Nine Circle logo
        CLAY(CLAY_ID("logo box"), {
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_FIT()
                },
                .childAlignment = {
                    .x = CLAY_ALIGN_X_CENTER,
                    .y = CLAY_ALIGN_Y_TOP
                },
                .padding = {
                    .top = 16
                }
            },
        }) {
            CLAY(CLAY_ID("logo"), {
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_FIXED(560),
                        .height = CLAY_SIZING_FIXED(85)
                    }
                },
                .image = {
                    .imageData = &(data->images.nineCircleLogo)
                }
            }) {}
        }
        // (optional) help + stats button
        // search + floating autocomplete
        // for loop over each guess object
        CLAY_AUTO_ID({
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_GROW()
                },
                .childAlignment = {
                    .x = CLAY_ALIGN_X_CENTER,
                    .y = CLAY_ALIGN_Y_CENTER
                }
            }
        }) {
            CLAY_TEXT(
                CLAY_STRING("text test"), {
                    .fontId = 0,
                    .fontSize = 72,
                    .textColor = {255, 255, 255, 255}
                }
            );
        }
    }

    return Clay_EndLayout(0);
}