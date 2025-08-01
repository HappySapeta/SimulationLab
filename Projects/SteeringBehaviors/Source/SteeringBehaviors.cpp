#include "Common/WindowConfiguration.h"
#include <raylib/raylib.h>

int main()
{
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    while (!WindowShouldClose())
    {
        PollInputEvents();
        if (IsKeyPressed(KEY_ESCAPE))
        {
            CloseWindow();
        }
        
        BeginDrawing();
        {
            ClearBackground(LIGHTGRAY);
        }
        EndDrawing();
    }
    return 0;
}