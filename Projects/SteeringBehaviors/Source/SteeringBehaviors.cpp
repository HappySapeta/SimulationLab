#include "Agent.h"
#include "AgentManager.h"
#include "Core/WindowConfiguration.h"

#include <raylib/raylib.h>

int main()
{
    AgentManager Manager;
    Manager.Initialize();
    Manager.SetCurrentBehavior(EBehaviorIndex::SEEK);
    Manager.SpawnAgent();
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    while (!WindowShouldClose())
    {
        PollInputEvents();
        ClearBackground(LIGHTGRAY);
        BeginDrawing();
        {
            Manager.Update(GetFrameTime());
        }
        EndDrawing();
    }
    
    return 0;
}
