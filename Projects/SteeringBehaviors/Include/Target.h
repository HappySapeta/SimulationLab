#pragma once
#include "Agent.h"

enum class EMovementMode : int
{
	NONE,
	DIAGONAL,
	CIRCLE,
	XAXIS,
	YAXIS,
	COUNT
};

inline EMovementMode ToMovementMode(const int Index)
{
	using UnderlyingType = std::underlying_type_t<EMovementMode>;
	EMovementMode Mode = Index >= static_cast<UnderlyingType>(EMovementMode::NONE) &&
						 Index < static_cast<UnderlyingType>(EMovementMode::COUNT) ?
						 static_cast<EMovementMode>(Index) : EMovementMode::NONE;

	return Mode; 
}

class Target : public Agent
{
public:
	virtual ~Target() = default;
	void MoveWithMouseClick();
	virtual void Update(const float DeltaTime) override;
	virtual void Draw() override;

	void SetVelocity(const Vec2& Velocity) { Velocity_ = Velocity; }
	void SetMovementMode(EMovementMode TargetMovementMode) { TargetMovementMode_ = TargetMovementMode; }

private:

	bool bIsCapturedByMouse = false;
	EMovementMode TargetMovementMode_ = EMovementMode::NONE;
};
