#include <raylib/raylib.h>

#include "Agent.h"
#include "Core/WindowConfiguration.h"

int main()
{
    Agent Agent;
    Agent.SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});
    
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    while (!WindowShouldClose())
    {
        PollInputEvents();
        ClearBackground(LIGHTGRAY);
        BeginDrawing();
        {
            Agent.Draw();
        }
        EndDrawing();
    }
    
    return 0;
}
