#include <raylib/raylib.h>
#include "Core/WindowConfiguration.h"

int main()
{
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    while (!WindowShouldClose())
    {
        PollInputEvents();
        ClearBackground(LIGHTGRAY);
        BeginDrawing();
        {
           
        }
        EndDrawing();
    }
    
    return 0;
}
