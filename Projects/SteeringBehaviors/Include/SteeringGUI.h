#pragma once
#include "CommonTypes.h"
#include "Core/GUIHelper.h"

constexpr int SCENE_TEXTSIZE = 20;

class SteeringGUI : public GUIHelper
{
public:
	SteeringGUI(const uint16_t Width, const uint16_t Height)
		:GUIHelper(Width, Height)
	{}
	virtual void Draw() override;
	
	ESceneIndex GetSceneIndex()
	{
		return ToSceneIndex(SceneIndex_);
	}
	
private:
	bool bBehaviorDropdownEdit_ = false;
	int SceneIndex_ = 0;
};
