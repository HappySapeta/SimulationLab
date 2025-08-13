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
	int GetBehaviorValue() { return BehaviorValue_ + 1; }
	int GetTargetMovementMode() { return bAutoMoveTarget_ ? TargetMovementMode_ + 1: 0 ; }
	bool GetShouldArriveAtTarget() { return bShouldArriveAtTarget_; }

private:
	int SpawnButton_ = 0;
	int DeSpawnButton_ = 0;
	int BehaviorValue_ = 0;
	int TargetMovementMode_ = 0;
	bool bShouldArriveAtTarget_ = false;
	
private:
	bool bAutoMoveTarget_ = false;
	bool bBehaviorDropdownEdit_ = false;
	bool bTargetMovementEdit_ = false;
};
