#pragma once
#include <cstdint>
#include <raylib/raylib.h>

constexpr uint8_t SL_AGENT_SIZE = 20;
constexpr Color SL_AGENT_COLOR = RED;
constexpr float SL_AGENT_MAXSPEED = 300.0f;
constexpr float SL_AGENT_SEEK_STRENGTH = 1.0f;
constexpr float SL_AGENT_FLEE_STRENGTH = 1.0f;
constexpr float SL_AGENT_INTERCEPT_LOOKAHEAD = 1.0f;
constexpr float SL_AGENT_ARRIVAL_RADIUS = 300.0f;

constexpr uint8_t SL_TARGET_SIZE = 20;
constexpr Color SL_TARGET_COLOR = YELLOW;
constexpr float SL_TARGET_MOVEMENTSPEED = 200;
constexpr float SL_TARGET_MOVEMENTRADIUS = 500;