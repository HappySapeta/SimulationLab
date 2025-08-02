#include <raylib/raylib.h>
#include "Core/WindowConfiguration.h"

int main()
{
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Welcome!");
    while (!WindowShouldClose())
    {
        PollInputEvents();
        if (IsKeyPressed(KEY_ESCAPE))
        {
            CloseWindow();
        }
        
        BeginDrawing();
        {
            ClearBackground(LIGHTGRAY);

            const char* Title = "Welcome to SimulationLab!";
            constexpr uint16_t FontSize = 30;
            const uint16_t TextLength = MeasureText(Title, FontSize);
            DrawText(Title, SL_WINDOW_WIDTH / 2 - TextLength / 2, SL_WINDOW_HEIGHT / 2 - FontSize / 2, FontSize, DARKGRAY);
        }
        EndDrawing();
    }
    return 0;
}