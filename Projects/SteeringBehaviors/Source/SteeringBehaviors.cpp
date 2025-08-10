#include "Agent.h"
#include "AgentManager.h"
#include "Core/WindowConfiguration.h"

#include <raylib/raylib.h>

int main()
{
    AgentManager Manager({SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT});
    Manager.SetCurrentBehavior(EBehaviorIndex::SEEK);
    
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");

    while (!WindowShouldClose())
    {
        ClearBackground(LIGHTGRAY);
        BeginDrawing();
        {
            Manager.Update(GetFrameTime());
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
