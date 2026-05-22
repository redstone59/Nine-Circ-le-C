#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define CLAY_IMPLEMENTATION
#include "../lib/clay/clay.h"
#include "../lib/clay/renderers/raylib/clay_renderer_raylib.c"

void HandleClayErrors(Clay_ErrorData errorData) {
    // See the Clay_ErrorData struct for more information
    printf("%s", errorData.errorText.chars);
}

int main(void) {
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(arena, (Clay_Dimensions){.width = 1280, .height = 720}, (Clay_ErrorHandler) { HandleClayErrors });

    Clay_Raylib_Initialize(1280, 720, "Nine Circ-le", FLAG_WINDOW_RESIZABLE);
    
    Font fonts[0];
    
    while (!WindowShouldClose()) {
        Clay_SetLayoutDimensions((Clay_Dimensions){
            .width = GetScreenWidth(),
            .height = GetScreenHeight()
        });

        Clay_BeginLayout();

        CLAY(
            CLAY_ID("test"), {
            .backgroundColor = {255, 0, 0, 255},
            .layout = {
                .padding = CLAY_PADDING_ALL(16),
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_GROW()
                }
            }
        }) {}

        Clay_RenderCommandArray renderCommands = Clay_EndLayout(0);

        BeginDrawing();
        ClearBackground(MAGENTA);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
    return 0;
}