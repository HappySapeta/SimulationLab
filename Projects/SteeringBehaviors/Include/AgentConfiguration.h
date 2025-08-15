#pragma once
#include <cstdint>
#include <raylib/raylib.h>

constexpr uint8_t SL_AGENT_SIZE = 20;
constexpr Color SL_AGENT_COLOR = MAROON;
constexpr float SL_AGENT_MAXSPEED = 1000.0f;
constexpr float SL_AGENT_MAXFORCE = 700.0f;
constexpr float SL_AGENT_SEEK_STRENGTH = 1.0f;
constexpr float SL_AGENT_FLEE_STRENGTH = 1.0f;
constexpr float SL_AGENT_FLEE_RADIUS = 500.0f;
constexpr float SL_AGENT_INTERCEPT_LOOKAHEAD = 0.5f;
constexpr float SL_AGENT_PURSUE_RADIUS = 100.0f;
constexpr float SL_AGENT_ARRIVAL_RADIUS = 300.0f;

constexpr uint8_t SL_TARGET_SIZE = 20;
constexpr Color SL_TARGET_COLOR = BLACK;
constexpr float SL_TARGET_MOVEMENTSPEED = 200;