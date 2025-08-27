#include "AgentManager.h"
#include "Core/WindowConfiguration.h"
#include "raylib/raylib.h"
#include "SteeringGUI.h"

int main()
{
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Steering Behaviors");
    SteeringGUI GUI(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT);
    AgentManager Manager({SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT});

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            Manager.ChangeScene(GUI.GetSceneIndex());
            Manager.Update(GetFrameTime());
            GUI.Draw();
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
