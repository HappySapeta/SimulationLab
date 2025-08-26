#pragma once

#include "Agent.h"
#include "AgentConfiguration.h"
#include "Core/RaylibHelper.h"

#include <random>
#include <Core/Vector.h>

#ifdef DEBUG
#define DRAW_BEHAVIORS
#endif

using Vec2 = SL::Vec2;
struct SteeringData
{
	Vec2 AgentPosition;
	Vec2 AgentVelocity;
	Vec2 TargetPosition;
	Vec2 TargetVelocity;
};

class Behaviors
{
public:
	static Vec2 Seek(const SteeringData& Data)
	{
		const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
		const Vec2 DesiredVelocity = TargetHeading * SL_AGENT_MAXSPEED;

		const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
		const Vec2 ForceToApply = VelocityDifference * SL_AGENT_SEEK_STRENGTH;

#ifdef DRAW_BEHAVIORS
		{
			DrawLineV(Data.AgentPosition, Data.TargetPosition, GRAY);
		}
#endif

		return ForceToApply;
	}
	
	static Vec2 Flee(const SteeringData& Data, const float FleeRadius)
	{
		const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
		const Vec2 DesiredVelocity = -1 * TargetHeading * SL_AGENT_MAXSPEED;

		const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
		const Vec2 ForceToApply = VelocityDifference * SL_AGENT_FLEE_STRENGTH;

		if (Vec2::Distance(Data.TargetPosition, Data.AgentPosition) <= FleeRadius)
		{
#ifdef DRAW_BEHAVIORS
			{
				DrawLineV(Data.AgentPosition, Data.TargetPosition, RED);
			}
#endif
			return ForceToApply;
		}

		return {0,0};
	}

	static Vec2 GetPursueTarget(const SteeringData& Data, const float PursueDistance)
	{
		const Vec2 TargetHeading = (Data.TargetPosition - Data.AgentPosition).GetNormal();
		const Vec2 PursueTarget = Data.TargetPosition - (TargetHeading * PursueDistance);

		return PursueTarget;
	}
	
	static Vec2 Pursue(const SteeringData& Data, const float PursueDistance)
	{
		const Vec2 PursueTarget = GetPursueTarget(Data, PursueDistance);
		const Vec2 ForceToApply = Seek({Data.AgentPosition, Data.AgentVelocity, PursueTarget, Data.TargetVelocity});

#ifdef DRAW_BEHAVIORS
		{
			DrawLineV(Data.AgentPosition, PursueTarget, WHITE);
			DrawCircleV(PursueTarget, 5.0f, SKYBLUE);
		}
#endif

		return ForceToApply;
	}
	
	static Vec2 Intercept(const SteeringData& Data, const float InterceptLookahead)
	{
		const Vec2 TargetFuturePosition = Data.TargetPosition + Data.TargetVelocity * InterceptLookahead;
		const Vec2 TargetHeading = (TargetFuturePosition - Data.AgentPosition).GetNormal();
		
		const Vec2 DesiredVelocity = TargetHeading * SL_AGENT_MAXSPEED;
		const Vec2 VelocityDifference = DesiredVelocity - Data.AgentVelocity;
		const Vec2 ForceToApply = VelocityDifference * SL_AGENT_SEEK_STRENGTH;

#ifdef DRAW_BEHAVIORS
		{
			DrawLineV(Data.AgentPosition, TargetFuturePosition, WHITE);
			DrawCircleV(TargetFuturePosition, 5.0f, YELLOW);
		}
#endif

		return ForceToApply;
	}
	
	static Vec2 Evade(const SteeringData& Data)
	{
		const Vec2 TargetFuture = Data.TargetPosition + Data.TargetVelocity * SL_AGENT_INTERCEPT_LOOKAHEAD;

		const Vec2 ForceToApply = Flee({Data.AgentPosition, Data.AgentVelocity, TargetFuture, Data.TargetVelocity}, SL_AGENT_FLEE_RADIUS);
		if (Vec2::Distance(Data.TargetPosition, Data.AgentPosition) <= SL_AGENT_FLEE_RADIUS)
		{
			return ForceToApply;
		}

		return {0,0};
	}
	
	static Vec2 Wander(const SteeringData& Data, float& WanderTheta, const float WanderRadius = 100, const float WanderLookahead = 200)
	{
		std::random_device RandomDevice;
		std::mt19937 Generator(RandomDevice());
		std::uniform_real_distribution<float> UniformDist(-SL_AGENT_WANDER_CHANGE, SL_AGENT_WANDER_CHANGE);
		
		const Vec2 WanderCenter = Data.AgentPosition + Data.AgentVelocity.GetNormal() * WanderLookahead;
		WanderTheta += UniformDist(Generator);
		
		const Vec2 RandPos =
		{
			WanderCenter.x + (WanderRadius * std::cos(WanderTheta)),
			WanderCenter.y + (WanderRadius * std::sin(WanderTheta))
		};

#ifdef DRAW_BEHAVIORS
		{
			DrawCircleLinesV(WanderCenter, WanderRadius, BLACK);
			DrawCircleV(RandPos, 5.0f, RED);
		}
#endif

		const Vec2 Force = Seek({Data.AgentPosition, Data.AgentVelocity, RandPos, {0,0}});
		return Force;
	}
	
	static Vec2 Arrive(const SteeringData& Data, const float ArrivalDistance)
	{
		const Vec2& AgentVelocity = Data.AgentVelocity;
		const float DistanceToTarget = Vec2::Distance(Data.TargetPosition, Data.AgentPosition);
		if (DistanceToTarget <= ArrivalDistance)
		{
			const float SlowingFactor = 1.0f - (DistanceToTarget / ArrivalDistance);
			const Vec2 DesiredVelocity = (Data.TargetPosition - Data.AgentPosition).GetNormal() * SL_AGENT_MAXSPEED * -1 * SlowingFactor;

#ifdef DRAW_BEHAVIORS
			{
				Color FarColor = Color(255, 240, 0, 255);
				Color CloseColor = Color(255, 0, 0, 255);
				Color LineColor = SL::ColorHelper::InterpColor(FarColor, CloseColor, SlowingFactor);
		
				DrawLineV(Data.AgentPosition, Data.TargetPosition, LineColor);
			}
#endif
		
			const Vec2 ForceToApply = DesiredVelocity - AgentVelocity;
			return ForceToApply;
		}

		return {0,0};
	}
};
