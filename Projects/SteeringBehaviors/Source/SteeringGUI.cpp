#include "SteeringGUI.h"
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

void SteeringGUI::Draw()
{
	ClearBackground(LIGHTGRAY);

	// Scene selection box
	{
		GuiGroupBox(Rectangle{AnchorTopLeft.x + 10, AnchorTopLeft.y + 10, 230, 70}, "CHOOSE SCENE");
	}

	// Behavior select dropdown box.
	{
		if (GuiDropdownBox(Rectangle{AnchorTopLeft.x + 20, AnchorTopLeft.y + 20, 210, 50}, "SEEK;FLEE;INTERCEPT;PURSUE;EVADE;WANDER", &BehaviorValue_, bBehaviorDropdownEdit_))
		{
			bBehaviorDropdownEdit_ = !bBehaviorDropdownEdit_;
		}
	}
}
