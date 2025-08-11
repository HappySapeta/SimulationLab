#pragma once
#include "Agent.h"

class Target : public Agent
{
public:
	virtual ~Target() = default;
	void MoveWithMouseClick();
	virtual void Update(const float DeltaTime) override;
	virtual void Draw() override;

	void SetVelocity(const Vec2& Velocity) { Velocity_ = Velocity; }

private:

	bool bIsCapturedByMouse = false;
};
