#pragma once
#include "Core/Vector.h"

using Vec2 = SL::Vec2;

static Vec2 Vertices[]
{
	{ 1.0f,  0.0f},
	{-0.6f, -0.8f},
	{-0.6f,  0.8f},
};

struct Agent
{
	Agent();
	void Draw();
	void Update(const float DeltaTime);
	void Reset();
	
	Vec2 Position;
	Vec2 Velocity;
	Vec2 NetForce;
	float Size;
};
