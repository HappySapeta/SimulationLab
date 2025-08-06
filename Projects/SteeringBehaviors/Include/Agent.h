#pragma once
#include <vector>
#include "Core/Vector.h"

class SteeringBehaviorBase;
using Vec2 = SL::Vec2;

static Vec2 TriangleVertices[]
{
	{ 1.0f,  0.0f},
	{-0.6f, -0.8f},
	{-0.6f,  0.8f},
};

class Agent
{
public:
	Agent()
	: Position_(0,0), Velocity_(0,0), NetForce_(0,0)
	{}
	
	Agent(const Vec2& StartingPosition, const Vec2& StartingVelocity)
	: Position_(StartingPosition), Velocity_(StartingVelocity)
	{}
	
public:
	void AddForce(const Vec2 Force);
	void Update(const float DeltaTime);
	void Draw();
	void Reset();

	Vec2 GetVelocity() const { return Velocity_; }
	Vec2 GetPosition() const { return Position_; }

private:
	Vec2 Position_;
	Vec2 Velocity_;
	Vec2 NetForce_;
};
