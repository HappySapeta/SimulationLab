#pragma once
#include <vector>
#include "Core/Vector.h"

class SteeringBehaviorBase;
using Vec2 = SL::Vec2;

class Agent
{
public:
	Agent()
	: Position_(0,0), Velocity_(0,0), NetForce_(0,0)
	{}
	
	Agent(const Vec2& StartingPosition, const Vec2& StartingVelocity)
	: Position_(StartingPosition), Velocity_(StartingVelocity), NetForce_(0,0)
	{}
	
public:
	void AddForce(const Vec2 Force);
	virtual void Update(const float DeltaTime);
	virtual void Draw();
	void Reset();
	
	Vec2 GetVelocity() const { return Velocity_; }
	Vec2 GetPosition() const { return Position_; }
	void SetPosition(const Vec2& Position) { Position_ = Position; }

protected:
	Vec2 Position_;
	Vec2 Velocity_;
	Vec2 NetForce_;
};
