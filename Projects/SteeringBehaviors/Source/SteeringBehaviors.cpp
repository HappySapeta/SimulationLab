#include <raylib/raylib.h>

#include "Agent.h"
#include "Core/WindowConfiguration.h"

int main()
{
    Agent Agent({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2}, {0, 0});
    
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    while (!WindowShouldClose())
    {
        PollInputEvents();
        ClearBackground(LIGHTGRAY);
        BeginDrawing();
        {
            Agent.Update(GetFrameTime());
            Agent.Draw();
        }
        EndDrawing();
    }
    
    return 0;
}
