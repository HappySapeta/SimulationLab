#include "Agent.h"
#include <raylib/raylib.h>
#include "AgentConfiguration.h"
#include "Behaviors.h"

static Vec2 TriangleVertices[]
{
	Vec2{ 1.0f,  0.0f},
	Vec2{-0.6f, -0.8f},
	Vec2{-0.6f,  0.8f},
};

void Agent::AddForce(const Vec2 Force)
{
	NetForce_ += Force;
}

void Agent::Update(const float DeltaTime)
{
	NetForce_ = NetForce_.GetNormal() * std::min(SL_AGENT_MAXFORCE, NetForce_.GetLength());
	
	Velocity_ = Velocity_ + NetForce_ * DeltaTime;
	Velocity_ = Velocity_.GetNormal() * std::min(Velocity_.GetLength(), SL_AGENT_MAXSPEED);
	
	Position_ = Position_ + Velocity_ * DeltaTime;
	NetForce_ = Vec2{0, 0};
}

void Agent::Draw()
{
	const Vec2 Direction = Velocity_.GetNormal();
	float Angle = atan2(Direction.y , Direction.x);
	static auto Rotate = [](const Vec2& V, const float Angle) -> Vec2
	{
		return
		{
			V.x * cos(Angle) - V.y * sin(Angle),
			V.x * sin(Angle) + V.y * cos(Angle)
		};
	};
	Vec2 V1 = Rotate(TriangleVertices[0], Angle) * SL_AGENT_SIZE + Position_;
	Vec2 V2 = Rotate(TriangleVertices[1], Angle) * SL_AGENT_SIZE + Position_;
	Vec2 V3 = Rotate(TriangleVertices[2], Angle) * SL_AGENT_SIZE + Position_;
	DrawTriangle(V1, V2, V3, SL_AGENT_COLOR);
}

void Agent::Reset()
{
	Velocity_ = Vec2{0,0};
	Position_ = Vec2{0,0};
	NetForce_ = Vec2{0,0};
}