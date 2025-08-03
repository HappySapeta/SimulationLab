#include <raylib/raylib.h>
#include "Agent.h"
#include "Core/WindowConfiguration.h"

int main()
{
    Agent Agent;
    Agent.Position = {200,200};
    Agent.Size = 10.0f;
    Agent.Velocity = {10,10};
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
