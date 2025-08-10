#include "Core/GUIHelper.h"

Vec2 GUIHelper::GetAnchorPosition(EGUIAnchor Anchor)
{
	switch (Anchor)
	{
		case EGUIAnchor::TOPLEFT:
		{
			return {0.0f, 0.0f};
		}
		case EGUIAnchor::TOPRIGHT:
		{
			return {(float)ScreenWidth_, 0.0f};
		}
		case EGUIAnchor::BOTTOMLEFT:
		{
			return {0, (float)ScreenHeight_};
		}
		case EGUIAnchor::BOTTOMRIGHT:
		{
			return {(float)ScreenWidth_, (float)ScreenHeight_};
		}
		case EGUIAnchor::CENTER:
		{
			return {ScreenWidth_ / 2.0f, ScreenHeight_ / 2.0f};
		}
		case EGUIAnchor::CENTERTOP:
		{
			return {ScreenWidth_ / 2.0f, 0};
		}
		case EGUIAnchor::CENTERLEFT:
		{
			return {0, ScreenWidth_ / 2.0f};
		}
		case EGUIAnchor::CENTERRIGHT:
		{
			return {(float)ScreenWidth_, ScreenHeight_ / 2.0f};
		}
		case EGUIAnchor::CENTERBOTTOM:
		{
			return {ScreenWidth_ / 2.0f, (float)ScreenHeight_};
		}
	}

	return {0,0};
}
