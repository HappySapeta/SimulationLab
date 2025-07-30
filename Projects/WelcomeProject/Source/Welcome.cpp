#include <iostream>
#include "raylib/raylib.h"

constexpr uint16_t WindowWidth = 1280;
constexpr uint16_t WindowHeight = 720;

int main()
{
    InitWindow(1280, 720, "Welcome!");
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
            DrawText(Title, WindowWidth / 2 - TextLength / 2, WindowHeight / 2 - FontSize / 2, FontSize, DARKGRAY);
        }
        EndDrawing();
    }
    return 0;
}