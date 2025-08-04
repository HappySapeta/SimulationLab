#include "Agent.h"
#include <raylib/raylib.h>

Agent::Agent()
	: Position(0,0), Velocity(0,0), NetForce(0,0), Size(1.0f)
{}

void Agent::Draw()
{
	const Vec2 Direction = Velocity.GetNormal();
	float Angle = atan2(Direction.y , Direction.x);
	static auto Rotate = [](const Vec2& V, const float Angle) -> Vec2
	{
		return
		{
			V.x * cos(Angle) - V.y * sin(Angle),
			V.x * sin(Angle) + V.y * cos(Angle)
		};
	};
	Vec2 V1 = Rotate(Vertices[0], Angle) * Size + Position;
	Vec2 V2 = Rotate(Vertices[1], Angle) * Size + Position;
	Vec2 V3 = Rotate(Vertices[2], Angle) * Size + Position;
	DrawTriangle(V1, V2, V3, RED);
}

void Agent::Reset()
{
	Velocity = {0,0};
	Position = {0,0};
	NetForce = {0,0};
	Size = 1.0f;
}

void Agent::AddForce(const Vec2& Force)
{
	NetForce += Force;
}

void Agent::SetPosition(const Vec2& NewPosition)
{
	Position = NewPosition;
}

void Agent::SetSize(const float NewSize)
{
	Size = NewSize;
}

void Agent::Update(const float DeltaTime)
{
	Velocity = Velocity + NetForce * DeltaTime;
	Position = Position + Velocity * DeltaTime;
	NetForce = {0, 0};
}
