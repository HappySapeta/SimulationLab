#pragma once

#include <Core/Vector.h>

using Vec2 = SL::Vec2;
struct SteeringData
{
	Vec2 AgentPosition;
	Vec2 AgentVelocity;
	Vec2 TargetPosition;
	Vec2 TargetVelocity;
};

class SteeringBehaviorBase
{
public:
	SteeringBehaviorBase() = default;
	virtual ~SteeringBehaviorBase() = default;
	virtual Vec2 GetSteeringForce(const SteeringData& Data) = 0;
};

class SeekBehavior : public SteeringBehaviorBase
{
public:
	virtual Vec2 GetSteeringForce(const SteeringData& Data) override;
};

class FleeBehavior : public SteeringBehaviorBase
{
public:
	virtual Vec2 GetSteeringForce(const SteeringData& Data) override;
};

class InterceptBehavior : public SteeringBehaviorBase
{
public:
	SteeringData GetInterceptionData() const { return InterceptionData_; }
	virtual Vec2 GetSteeringForce(const SteeringData& Data) override;

private:
	SteeringData InterceptionData_;
};

class PursuitBehavior : public SteeringBehaviorBase
{
public:
	SteeringData GetPursuitData() { return PursuitData_; }
	virtual Vec2 GetSteeringForce(const SteeringData& Data) override;

private:
	SteeringData PursuitData_;
};

class EvasionBehavior : public SteeringBehaviorBase
{
public:
	virtual Vec2 GetSteeringForce(const SteeringData& Data) override;
};

class WanderingBehavior : public SteeringBehaviorBase
{
public:
	virtual Vec2 GetSteeringForce(const SteeringData& Data) override;
};

class ArriveBehavior : public SteeringBehaviorBase
{
public:
	static Vec2 GetSteeringForce(const SteeringData& Data);
};