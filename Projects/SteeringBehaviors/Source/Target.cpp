#include "Target.h"
#include "AgentConfiguration.h"
#include "Core/WindowConfiguration.h"

void Target::Update(const float DeltaTime)
{
	switch (TargetMovementMode_)
	{
		case EMovementMode::NONE:
		{
			MoveWithMouseClick();
			return;
		}
		case EMovementMode::DIAGONAL:
		{
			Velocity_ = Vec2{1, 1} * SL_TARGET_MOVEMENTSPEED;
			break;
		}
		case EMovementMode::CIRCLE:
		{
			static float Angle = 0.0f;
			Velocity_ = {0, 0};

			constexpr float MovmentRadius = SL_WINDOW_HEIGHT / 2.5f;
			const float PosX = SL_WINDOW_WIDTH / 2 + MovmentRadius * std::cos(Angle);
			const float PosY = SL_WINDOW_HEIGHT / 2 + MovmentRadius * std::sin(Angle);
			Position_ = {PosX, PosY};
			Angle += DeltaTime;
			if (Angle >= 2 * PI)
			{
				Angle = 0.0f;
			}
		}
		case EMovementMode::XAXIS:
		{
			Velocity_ = Vec2{1, 0} * SL_TARGET_MOVEMENTSPEED;
			break;
		}
		case EMovementMode::YAXIS:
		{
			Velocity_ = Vec2{0, 1} * SL_TARGET_MOVEMENTSPEED;
			break;
		}
		default:
			break;
	}
	Agent::Update(DeltaTime);
}

void Target::Draw()
{
	DrawCircleV(Position_, SL_TARGET_SIZE, SL_TARGET_COLOR);
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
