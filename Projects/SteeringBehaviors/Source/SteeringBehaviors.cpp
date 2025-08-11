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
        ClearBackground(LIGHTGRAY);
        BeginDrawing();
        {
            Manager.Update(GetFrameTime());
            GUI.Draw();
            Manager.SetCurrentBehavior((EBehaviorIndex)(GUI.GetBehaviorValue()));
            if (GUI.GetSpawnButtonValue())
            {
                Manager.SpawnAgent();
            }
            if (GUI.GetDeSpawnButtonValue())
            {
                Manager.DeSpawnAll();
            }
            Manager.SetArriveBehavior(GUI.GetShouldArriveAtTarget());
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
