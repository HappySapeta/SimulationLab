#pragma once
#include "Core/GUIHelper.h"

class SteeringGUI : public GUIHelper
{
public:
	SteeringGUI(const uint16_t Width, const uint16_t Height)
		:GUIHelper(Width, Height)
	{}
	virtual void Draw() override;
	
	int GetBehaviorValue() { return BehaviorValue_ + 1; }

private:
	int BehaviorValue_ = 0;
	
private:
	bool bBehaviorDropdownEdit_ = false;
};
