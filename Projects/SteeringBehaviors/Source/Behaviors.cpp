#include "Behaviors.h"

#include "Agent.h"
#include "AgentConfiguration.h"

Vec2 SeekBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
	const Vec2 DesiredVelocity = TargetHeading * SL_AGENT_MAXSPEED;

	const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
	const Vec2 ForceToApply = VelocityDifference * SL_AGENT_SEEK_STRENGTH;

	return ForceToApply;
}

Vec2 FleeBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
	const Vec2 DesiredVelocity = -1 * TargetHeading * SL_AGENT_MAXSPEED;

	const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
	const Vec2 ForceToApply = VelocityDifference * SL_AGENT_FLEE_STRENGTH;

	if (Vec2::Distance(Data.TargetPosition, Data.AgentPosition) <= SL_AGENT_FLEE_RADIUS)
	{
		return ForceToApply;
	}

	return {0,0};
}

Vec2 InterceptBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetFuturePosition = Data.TargetPosition + Data.TargetVelocity * SL_AGENT_INTERCEPT_LOOKAHEAD;
	const Vec2 TargetHeading = (TargetFuturePosition - Data.AgentPosition).GetNormal();

	const Vec2 DesiredVelocity = TargetHeading * SL_AGENT_MAXSPEED;
	const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
	const Vec2 ForceToApply = VelocityDifference * SL_AGENT_SEEK_STRENGTH;

	return ForceToApply;
}

Vec2 PursuitBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
	const Vec2 PursueTarget = Data.TargetPosition + (-1 * TargetHeading) * SL_AGENT_PURSUE_RADIUS;

	PursuitData_ = {Data.AgentPosition, Data.AgentVelocity, PursueTarget, Data.TargetVelocity};

	SeekBehavior Seek;
	const Vec2 ForceToApply = Seek.GetSteeringForce(PursuitData_);

	return ForceToApply;
}

Vec2 EvasionBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetFuture = Data.TargetPosition + Data.TargetVelocity * SL_AGENT_INTERCEPT_LOOKAHEAD;

	FleeBehavior Flee;
	const Vec2 ForceToApply = Flee.GetSteeringForce({Data.AgentPosition, Data.AgentVelocity, TargetFuture, Data.TargetVelocity});

	if (Vec2::Distance(Data.TargetPosition, Data.AgentPosition) <= SL_AGENT_FLEE_RADIUS)
	{
		return ForceToApply;
	}

	return {0,0};
}

Vec2 ArriveBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2& AgentVelocity = Data.AgentVelocity;
	const float DistanceToTarget = Vec2::Distance(Data.TargetPosition, Data.AgentPosition);
	if (DistanceToTarget <= SL_AGENT_ARRIVAL_RADIUS)
	{
		const float SlowingFactor = 1.0f - (DistanceToTarget / SL_AGENT_ARRIVAL_RADIUS);
		const Vec2 DesiredVelocity = (Data.TargetPosition - Data.AgentPosition).GetNormal() * SL_AGENT_MAXSPEED * -1 * SlowingFactor;

		const Vec2 ForceToApply = DesiredVelocity - AgentVelocity;
		return ForceToApply;
	}

	return {0,0};
}
