#include "Agent.h"
#include <raylib/raylib.h>

Agent::Agent()
	: Position_(0,0), Velocity_(0,0), NetForce_(0,0), Size_(1.0f)
{}

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
	Vec2 V1 = Rotate(Vertices[0], Angle) * Size_ + Position_;
	Vec2 V2 = Rotate(Vertices[1], Angle) * Size_ + Position_;
	Vec2 V3 = Rotate(Vertices[2], Angle) * Size_ + Position_;
	DrawTriangle(V1, V2, V3, RED);
}

void Agent::Reset()
{
	Velocity_ = {0,0};
	Position_ = {0,0};
	NetForce_ = {0,0};
	Size_ = 1.0f;
}

void Agent::AddForce(const Vec2& Force)
{
	NetForce_ += Force;
}

void Agent::SetPosition(const Vec2& NewPosition)
{
	Position_ = NewPosition;
}

void Agent::SetSize(const float NewSize)
{
	Size_ = NewSize;
}

void Agent::Update(const float DeltaTime)
{
	Velocity_ = Velocity_ + NetForce_ * DeltaTime;
	Position_ = Position_ + Velocity_ * DeltaTime;
	NetForce_ = {0, 0};
}
