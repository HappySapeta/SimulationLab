#include "Core/WindowConfiguration.h"

#include <chrono>
#include <thread>
#include <raylib/raylib.h>

constexpr float BASE_RADIUS = 150;
constexpr float SIN_AMPLITUDE = 100;

// Shared variables.
static std::atomic_bool G_IsRunning = true;
static std::_Atomic_floating<float> G_Radius = 0.0f;

void Initialize()
{
    InitWindow(SL_WINDOW_WIDTH, SL_WINDOW_HEIGHT, "Threads Test");
}

void UpdateLoop()
{
    while (G_IsRunning)
    {
        const std::chrono::duration<double> UpTime = std::chrono::high_resolution_clock::now().time_since_epoch();
        G_Radius = BASE_RADIUS + SIN_AMPLITUDE * std::sin(UpTime.count());

        PollInputEvents();
        if (WindowShouldClose())
        {
            G_IsRunning = false;
        }
    }
}

void RenderLoop()
{
    while (G_IsRunning)
    {
        ClearBackground(BLACK);
        BeginDrawing();
        {
            DrawCircle(SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2, G_Radius.load(), RED);
        }
        EndDrawing();
    }
}

int main()
{
    Initialize();

    std::thread UpdateThread(&UpdateLoop);
    RenderLoop();

    UpdateThread.join();
    
    CloseWindow();
    return 0;
}