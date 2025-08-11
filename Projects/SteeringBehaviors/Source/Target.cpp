#include "Target.h"
#include "AgentConfiguration.h"

#include <iostream>

void Target::Update(const float DeltaTime)
{
	Agent::Update(DeltaTime);
	MoveWithMouseClick();
}

void Target::Draw()
{
	DrawCircleV(Position_, SL_TARGET_SIZE, YELLOW);
	DrawText("Target", Position_.x, Position_.y, 10, RED);
}

void Target::MoveWithMouseClick()
{
	const Vec2 MousePosition = SL::ToVec2(GetMousePosition());
	
	if (Vec2::Distance(MousePosition, Position_) < SL_TARGET_SIZE || bIsCapturedByMouse)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			bIsCapturedByMouse = true;
			Position_ = MousePosition;
		}
	}

	if (bIsCapturedByMouse && IsMouseButtonUp(MOUSE_BUTTON_LEFT))
	{
		bIsCapturedByMouse = false;
	}
}
