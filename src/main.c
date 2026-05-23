#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define CLAY_IMPLEMENTATION
#include "./ui/app.c"

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
    
    Font fonts[] = {
        LoadFont(ASSET("PUSAB.otf"))
    };
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    NineCircleAppData appData = {0};
    NineCircleAppData_Initialise(&appData, fonts, arena);

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
        
        Clay_RenderCommandArray renderCommands = NineCircleApp_GetRenderCommands(&appData);

        BeginDrawing();
        ClearBackground(MAGENTA);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
    return 0;
}