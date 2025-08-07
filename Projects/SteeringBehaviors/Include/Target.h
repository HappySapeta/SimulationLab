#pragma once
#include "Agent.h"

enum class ETargetType : uint8_t
{
	SEEK,
	FLEE
};

class Target : public Agent
{
public:
	virtual ~Target() = default;
	virtual void Draw() override;

	ETargetType GetTargetType() const { return TargetType_; }
	void SetTargetType(const ETargetType Type) { TargetType_ = Type; }
	void SetVelocity(const Vec2& Velocity) { Velocity_ = Velocity; }

private:

	ETargetType TargetType_ = ETargetType::SEEK;
};
