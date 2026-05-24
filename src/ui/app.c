#include "../../lib/clay/clay.h"
#include "../../lib/clay/renderers/raylib/clay_renderer_raylib.c"

#include "guess_view.c"

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
    GuessArray* guesses;

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

Clay_RenderCommandArray NineCircleApp_GetRenderCommands(NineCircleAppData* data, float deltaTime) {
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
        .aspectRatio = 2257.0 / 1280.0,
        .image = {
            .imageData = &data->images.backgroundWidescreen
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
            }
        }) {
            CLAY(CLAY_ID("logo"), {
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_FIXED(560),
                        .height = CLAY_SIZING_FIXED(85)
                    }
                },
                .image = {
                    .imageData = &data->images.nineCircleLogo
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
                    .y = CLAY_ALIGN_Y_BOTTOM
                }
            }
        }) {
            CLAY(CLAY_ID("guess results view"), {
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_PERCENT(0.5),
                        .height = CLAY_SIZING_GROW()
                    },
                    .childAlignment = {
                        .x = CLAY_ALIGN_X_CENTER,
                        .y = CLAY_ALIGN_Y_TOP
                    },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM,
                    .childGap = 8
                },
                .clip = {
                    .vertical = true,
                    .childOffset = Clay_GetScrollOffset()
                }
            }) {
                for (int i = 0; i < data->guesses->count; i++) {
                    RenderGuessResult(&data->guesses->elements[i]);
                }
            }
    }}

    return Clay_EndLayout(deltaTime);
}