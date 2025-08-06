#pragma once
#include <cstdint>
#include <raylib/raylib.h>

constexpr uint8_t SL_AGENT_SIZE = 20;
constexpr Color SL_AGENT_COLOR = RED;
constexpr float SL_AGENT_MAXSPEED = 100.0f;
constexpr float SL_AGENT_SEEK_STRENGTH = 1.0f;
constexpr float SL_AGENT_FLEE_STRENGTH = 1.0f;
constexpr float SL_AGENT_INTERCEPT_LOOKAHEAD = 0.1f;