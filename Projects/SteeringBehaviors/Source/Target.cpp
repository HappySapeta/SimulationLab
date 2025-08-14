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

			constexpr float MovementRadius = SL_WINDOW_HEIGHT / 2.5f;
			const float PosX = SL_WINDOW_WIDTH / 2 + MovementRadius * std::cos(Angle);
			const float PosY = SL_WINDOW_HEIGHT / 2 + MovementRadius * std::sin(Angle);
			const Vec2 DesiredPosition = {PosX, PosY};
			
			Velocity_ = (DesiredPosition - GetPosition()) / DeltaTime;

			Angle += DeltaTime;
			if (Angle >= 2 * PI)
			{
				Angle = 0.0f;
			}

			break;
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
	NetForce_ = {0,0};
	Agent::Update(DeltaTime);
}

void Target::Draw()
{
	DrawCircleV(GetPosition(), SL_TARGET_SIZE, SL_TARGET_COLOR);
	DrawLineV(GetPosition(), GetPosition() + GetVelocity(), RED);
}

void Target::MoveWithMouseClick()
{
	const Vec2 MousePosition = SL::ToVec2(GetMousePosition());
	
	if (Vec2::Distance(MousePosition, GetPosition()) < SL_TARGET_SIZE || bIsCapturedByMouse)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			bIsCapturedByMouse = true;
			SetPosition(MousePosition);
		}
	}

	if (bIsCapturedByMouse && IsMouseButtonUp(MOUSE_BUTTON_LEFT))
	{
		bIsCapturedByMouse = false;
	}
}

void Target::SetPosition(const Vec2& NewPosition)
{
	const double CurrentTime = GetTime();
	Velocity_ = (NewPosition - Position_) / (CurrentTime - LastPositionUpdateTime_);
	Position_ = NewPosition;
	LastPositionUpdateTime_ = CurrentTime;
}
