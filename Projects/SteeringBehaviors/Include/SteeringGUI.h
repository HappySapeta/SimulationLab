#pragma once
#include "Core/GUIHelper.h"

class SteeringGUI : public GUIHelper
{
public:
	SteeringGUI(const uint16_t Width, const uint16_t Height)
		:GUIHelper(Width, Height)
	{}
	virtual void Draw() override;

	int GetSpawnButtonValue() { return SpawnButton_; }
	int GetDeSpawnButtonValue() { return DeSpawnButton_; }
	int GetBehaviorValue() { return BehaviorValue_; }
	bool GetShouldArriveAtTarget() { return bShouldArriveAtTarget_; }

private:

	int SpawnButton_ = 0;
	int DeSpawnButton_ = 0;
	int BehaviorValue_ = 0;
	bool bShouldArriveAtTarget_ = false;
	bool BehaviorDropdownEdit_ = false;
};
