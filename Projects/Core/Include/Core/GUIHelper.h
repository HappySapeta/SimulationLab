#pragma once
#include <cstdint>

#include "Core/Vector.h"

enum class EGUIAnchor
{
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT,
	CENTER,
	CENTERTOP,
	CENTERLEFT,
	CENTERRIGHT,
	CENTERBOTTOM
};

using Vec2 = SL::Vec2;

class GUIHelper
{
public:
	virtual ~GUIHelper() = default;
	
	virtual void Draw() {};
	void SetDimensions(const uint16_t Width, const uint16_t Height)
	{
		ScreenWidth_ = Width;
		ScreenHeight_ = Height;
	}

private:

	Vec2 GetAnchorPosition(EGUIAnchor Anchor);
	
	uint32_t GetScreenWidth(){ return ScreenWidth_; }
	uint32_t GetScreenHeight(){ return ScreenHeight_; }

private:

	uint32_t ScreenWidth_ = 1;
	uint32_t ScreenHeight_ = 1;
};
