#include "Behaviors.h"
#include "Agent.h"
#include "AgentConfiguration.h"
#include "Core/RaylibHelper.h"

#include <random>

#ifdef DEBUG
//#define DRAW_BEHAVIORS
#endif

Vec2 SeekBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
	const Vec2 DesiredVelocity = TargetHeading * SL_AGENT_MAXSPEED;

	const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
	const Vec2 ForceToApply = VelocityDifference * SL_AGENT_SEEK_STRENGTH;

#ifdef DRAW_BEHAVIORS
	DrawLineV(Data.AgentPosition, Data.TargetPosition, GRAY);
#endif

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
#ifdef DRAW_BEHAVIORS
		DrawLineV(Data.AgentPosition, Data.TargetPosition, RED);
#endif
		return ForceToApply;
	}

	return {0,0};
}

Vec2 InterceptBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetFuturePosition = Data.TargetPosition + Data.TargetVelocity * SL_AGENT_INTERCEPT_LOOKAHEAD;
	const Vec2 TargetHeading = (TargetFuturePosition - Data.AgentPosition).GetNormal();

	InterceptionData_ = {Data.AgentPosition, Data.AgentVelocity, TargetFuturePosition, Data.TargetVelocity};
	
	const Vec2 DesiredVelocity = TargetHeading * SL_AGENT_MAXSPEED;
	const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
	const Vec2 ForceToApply = VelocityDifference * SL_AGENT_SEEK_STRENGTH;

#ifdef DRAW_BEHAVIORS
	DrawLineV(Data.AgentPosition, TargetFuturePosition, WHITE);
	DrawCircleV(TargetFuturePosition, 5.0f, YELLOW);
#endif

	return ForceToApply;
}

Vec2 PursuitBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
	const Vec2 PursueTarget = Data.TargetPosition - (TargetHeading * SL_AGENT_PURSUE_RADIUS);

	PursuitData_ = {Data.AgentPosition, Data.AgentVelocity, PursueTarget, Data.TargetVelocity};

	SeekBehavior Seek;
	const Vec2 ForceToApply = Seek.GetSteeringForce(PursuitData_);

#ifdef DRAW_BEHAVIORS
	DrawLineV(Data.AgentPosition, PursueTarget, WHITE);
	DrawCircleV(PursueTarget, 5.0f, SKYBLUE);
#endif

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

Vec2 WanderingBehavior::GetSteeringForce(const SteeringData& Data)
{
	static float RandomAngle = 0.0f;
	std::random_device RandomDevice;
	std::mt19937 Generator(RandomDevice());
	std::uniform_real_distribution<float> Distribution(-PI/8, PI/8);
	
	RandomAngle += Distribution(Generator);
	const float PosX = SL_AGENT_WANDER_RADIUS * std::cos(RandomAngle);
	const float PosY = SL_AGENT_WANDER_RADIUS * std::sin(RandomAngle);
	const Vec2 RandomPos = Vec2{PosX, PosY} + Data.AgentPosition + (Data.AgentVelocity.GetNormal() * SL_AGENT_WANDER_RADIUS);

	SeekBehavior Seek;
	const Vec2 ForceToApply = Seek.GetSteeringForce({Data.AgentPosition, Data.AgentVelocity, RandomPos, Data.AgentVelocity});

	return ForceToApply;
}

Vec2 ArriveBehavior::GetSteeringForce(const SteeringData& Data)
{
	const Vec2& AgentVelocity = Data.AgentVelocity;
	const float DistanceToTarget = Vec2::Distance(Data.TargetPosition, Data.AgentPosition);
	if (DistanceToTarget <= SL_AGENT_ARRIVAL_RADIUS)
	{
		const float SlowingFactor = 1.0f - (DistanceToTarget / SL_AGENT_ARRIVAL_RADIUS);
		const Vec2 DesiredVelocity = (Data.TargetPosition - Data.AgentPosition).GetNormal() * SL_AGENT_MAXSPEED * -1 * SlowingFactor;


#ifdef DRAW_BEHAVIORS
		Color FarColor = Color(255, 240, 0, 255);
		Color CloseColor = Color(255, 0, 0, 255);
		Color LineColor = SL::ColorHelper::InterpColor(FarColor, CloseColor, SlowingFactor);
		
		DrawLineV(Data.AgentPosition, Data.TargetPosition, LineColor);
#endif
		
		const Vec2 ForceToApply = DesiredVelocity - AgentVelocity;
		return ForceToApply;
	}

	return {0,0};
}
