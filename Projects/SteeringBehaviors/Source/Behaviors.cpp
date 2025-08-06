#include "Behaviors.h"
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
	const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal() * -1;
	const Vec2 DesiredVelocity = TargetHeading * SL_AGENT_MAXSPEED;

	const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
	const Vec2 ForceToApply = VelocityDifference * SL_AGENT_FLEE_STRENGTH;

	return ForceToApply;
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
