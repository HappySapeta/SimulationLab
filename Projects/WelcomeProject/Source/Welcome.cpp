#include "raylib/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raylib/raygui.h"
#include "Core/WindowConfiguration.h"

int main()
{
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Welcome!");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(LIGHTGRAY);

            const char* Title = "Welcome to SimulationLab!";
            constexpr uint16_t FontSize = 30;
            const uint16_t TextLength = MeasureText(Title, FontSize);
            DrawText(Title, SL_WINDOW_WIDTH / 2 - TextLength / 2, SL_WINDOW_HEIGHT / 2 - FontSize / 2, FontSize, DARKGRAY);

            if (GuiButton(Rectangle{SL_WINDOW_WIDTH / 2 - 50, SL_WINDOW_HEIGHT / 2 + 50, 100, 40}, "CLOSE"))
            {
                CloseWindow();
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}