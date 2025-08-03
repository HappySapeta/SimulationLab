#include <raylib/raylib.h>
#include "Agent.h"
#include "Core/WindowConfiguration.h"

int main()
{
    Agent Agent;
    Agent.SetPosition({0, 0});
    Agent.SetSize(50.0f);

    float Value = 0.0f;
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    while (!WindowShouldClose())
    {
        PollInputEvents();
        ClearBackground(LIGHTGRAY);
        BeginDrawing();
        {
            const float DeltaTime = GetFrameTime();
            Agent.AddForce({50, Value});
            Agent.Update(DeltaTime);
            Agent.Draw();

            Value += DeltaTime * 50;
        }
        EndDrawing();
    }
    
    return 0;
}
