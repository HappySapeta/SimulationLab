#pragma once
#include "Core/Vector.h"
#include <cstdint>

using Vec2 = SL::Vec2;

class GUIHelper
{
public:
	virtual ~GUIHelper() = default;
	GUIHelper(const uint32_t Width, const uint32_t Height)
		:ScreenWidth(Width), ScreenHeight(Height),
		AnchorTopLeft(0.0f, 0.0f),
		AnchorTopRight((float)ScreenWidth, 0.0f),
		AnchorBottomLeft(0, (float)ScreenHeight),
		AnchorBottomRight((float)ScreenWidth, (float)ScreenHeight),
		AnchorCenter(ScreenWidth * 0.5f, ScreenHeight * 0.5f),
		AnchorCenterTop(ScreenWidth * 0.5f, 0),
		AnchorCenterLeft(0, ScreenHeight * 0.5f),
		AnchorCenterRight((float)ScreenWidth, ScreenHeight * 0.5f),
		AnchorCenterBottom(ScreenWidth * 0.5f, (float)ScreenHeight)
	{}
	virtual void Draw() = 0;
	
public:
	const uint32_t ScreenWidth;
	const uint32_t ScreenHeight;
	const Vec2 AnchorTopLeft;
	const Vec2 AnchorTopRight;
	const Vec2 AnchorBottomLeft;
	const Vec2 AnchorBottomRight;
	const Vec2 AnchorCenter;
	const Vec2 AnchorCenterTop;
	const Vec2 AnchorCenterLeft;
	const Vec2 AnchorCenterRight;
	const Vec2 AnchorCenterBottom;
};
