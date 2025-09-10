#include <string>
#include <raylib/raylib.h>

#include "Core/WindowConfiguration.h"

int main()
{
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Finite State Machines");

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        {
            const std::string Text = "Finite State Machines";
            constexpr float FontSize = 20.0f;
            const float TextSize = MeasureText(Text.c_str(), FontSize);
            DrawText(Text.c_str(), SL_WINDOW_WIDTH / 2 - TextSize / 2, SL_WINDOW_HEIGHT / 2 - FontSize / 2, FontSize, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
