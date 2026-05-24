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

    Clay_String creators[] = { CLAY_STRING("Zobros") }; 
    Level nineCirclesLevel = {
        .id = 4284013,
        .name = CLAY_STRING("Nine Circles"),
        .creators = creators,
        .creatorCount = 1
    };
    GuessResult testResult = {
        .difficulty = RELATIVE_HIGHER,
        .downloads = RELATIVE_LOWER,
        .length = RELATIVE_CORRECT,
        .likes = RELATIVE_HIGHER,
        .objectCount = RELATIVE_LOWER,
        .primaryColourCorrect = true,
        .secondaryColourCorrect = false
    };

    GuessResultView testView = {0};
    GuessResultView_Initialise(&testView, &nineCirclesLevel, &testResult);

    GuessArray testArray = {0};
    GuessArray_Initialise(&testArray, 16);
    GuessArray_Append(&testArray, testView);

    appData.guesses = &testArray;

#ifdef NINE_CIRCLE_DEBUG
    bool debugViewEnabled = true;
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
#ifdef NINE_CIRCLE_DEBUG
            if (IsKeyPressed(KEY_D)) {
                debugViewEnabled = !debugViewEnabled;
            }
            Clay_SetDebugModeEnabled(debugViewEnabled);

            if (IsKeyPressed(KEY_SPACE)) {
                GuessArray_Append(&testArray, testView);
                printf("Appended new entry to test array.\n");
            }
#endif
        
        Clay_RenderCommandArray renderCommands = NineCircleApp_GetRenderCommands(&appData, 0);

        BeginDrawing();
        ClearBackground(MAGENTA);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    GuessArray_Free(&testArray);
    Clay_Raylib_Close();
    return 0;
}