#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define CLAY_IMPLEMENTATION
#include "../lib/clay/clay.h"
#include "../lib/clay/renderers/raylib/clay_renderer_raylib.c"

#define ASSET(path) "./assets/" path

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

int main(void) {
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(
        arena, 
        (Clay_Dimensions) {
            .width = 1280, 
            .height = 720
        }, 
        (Clay_ErrorHandler) { HandleClayErrors }
    );
    
    Clay_Raylib_Initialize(
        1280, 720,
        "Nine Circ-le",
        FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT
    );
    
    typedef enum FontEnum {
        PUSAB,
        MAX    // Not a font, but used to iterate over fonts.
    } FontEnum;
    Font fonts[] = {
        LoadFont(ASSET("PUSAB.otf"))
    };
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);
    
    const Texture wsBackground = LoadTexture(ASSET("widescreen_background.png"));
    const Texture nineCircleLogo = LoadTexture(ASSET("logo.png"));

#ifdef NINE_CIRCLE_DEBUG
    Clay_SetDebugModeEnabled(true);
#endif

    while (!WindowShouldClose()) {
        Clay_SetLayoutDimensions((Clay_Dimensions){
            .width = GetScreenWidth(),
            .height = GetScreenHeight()
        });
        Clay_SetPointerState((Clay_Vector2) {
            .x = GetMouseX(),
            .y = GetMouseY()
        }, IsMouseButtonDown(0));
        Vector2 scrollVector = GetMouseWheelMoveV();
        Clay_UpdateScrollContainers(
            true,
            (Clay_Vector2) { 
                .x = scrollVector.x, 
                .y = scrollVector.y
            }, 
            0
        );
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
                .imageData = &wsBackground
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
                        .imageData = &nineCircleLogo
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

        Clay_RenderCommandArray renderCommands = Clay_EndLayout(0);

        BeginDrawing();
        ClearBackground(MAGENTA);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
    return 0;
}