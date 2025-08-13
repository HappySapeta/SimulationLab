#include "AgentManager.h"
#include "Core/WindowConfiguration.h"

#include <raylib/raylib.h>

#include "SteeringGUI.h"

int main()
{
    AgentManager Manager({SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT});
    Manager.SetCurrentBehavior(EBehaviorIndex::SEEK);

    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    SteeringGUI GUI(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            GUI.Draw();
            
            Manager.SetCurrentBehavior(GUI.GetBehaviorValue());
            if (GUI.GetSpawnButtonValue())
            {
                Manager.SpawnAgent();
            }
            if (GUI.GetDeSpawnButtonValue())
            {
                Manager.DeSpawnAll();
            }
            Manager.SetArriveBehavior(GUI.GetShouldArriveAtTarget());
            Manager.SetTargetMovementMode(GUI.GetTargetMovementMode());
            Manager.Update(GetFrameTime());
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
