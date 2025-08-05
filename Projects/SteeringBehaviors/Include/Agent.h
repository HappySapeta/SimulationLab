#pragma once
#include <vector>
#include "Core/Vector.h"

using Vec2 = SL::Vec2;

static Vec2 Vertices[]
{
	{ 1.0f,  0.0f},
	{-0.6f, -0.8f},
	{-0.6f,  0.8f},
};

class Agent
{
public:
	Agent();
	Agent(const Vec2& StartingPosition, const Vec2& StartingVelocity);
	
	void Draw();
	void Update(const float DeltaTime);
	void Reset();

private:
	void AddForce(const Vec2& Force);

private:
	Vec2 Position_;
	Vec2 Velocity_;
	Vec2 NetForce_;
};
