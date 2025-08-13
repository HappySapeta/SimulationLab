#include "SteeringGUI.h"
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

void SteeringGUI::Draw()
{
	// Agent Manager groupbox
	{
		GuiGroupBox(Rectangle{AnchorTopRight.x - 240, AnchorTopRight.y + 10, 230, 70}, "AGENT MANAGER");
		SpawnButton_ = GuiButton(Rectangle{AnchorTopRight.x - 230, AnchorTopRight.y + 20, 100, 50}, "SPAWN");
		DeSpawnButton_ = GuiButton(Rectangle{AnchorTopRight.x - 230 + 110, AnchorTopRight.y + 20, 100, 50}, "REMOVE ALL");
	}

	// Behavior Settings groupbox
	{
		GuiGroupBox(Rectangle{AnchorTopRight.x - 240, AnchorTopRight.y + 90, 230, 100}, "BEHAVIOR SETTINGS");

		// Arrive-at-Target checkbox.
		{
			int DefaultCheckPadding = GuiGetStyle(CHECKBOX, CHECK_PADDING);
			GuiSetStyle(CHECKBOX, CHECK_PADDING, 5);
			GuiCheckBox(Rectangle{AnchorTopRight.x - 190, AnchorTopRight.y + 160, 20, 20}, "Arrive at Target?", &bShouldArriveAtTarget_);
			GuiSetStyle(CHECKBOX, CHECK_PADDING, DefaultCheckPadding);
		}
	}

	// Target movement groupbox
	{
		GuiGroupBox(Rectangle{AnchorTopLeft.x + 10, AnchorTopLeft.y + 10, 230, 100}, "TARGET MOVEMENT");

		int DefaultCheckPadding = GuiGetStyle(CHECKBOX, CHECK_PADDING);
		GuiSetStyle(CHECKBOX, CHECK_PADDING, 5);
		GuiCheckBox(Rectangle{AnchorTopLeft.x + 20, AnchorTopLeft.y + 20, 20, 20}, "Auto move target?", &bAutoMoveTarget_);
		GuiSetStyle(CHECKBOX, CHECK_PADDING, DefaultCheckPadding);
		
		// Information label.
		if (!bAutoMoveTarget_)
		{
			GuiLabel(Rectangle{AnchorTopLeft.x + 40, AnchorTopLeft.y + 100, 210, 50}, "! Click and drag to move Target.");
		}
	}

	// Target movement choice
	{
		if (GuiDropdownBox(Rectangle{AnchorTopLeft.x + 20, AnchorTopLeft.y + 50, 210, 50}, "DIAGONAL;CIRCLE;X-AXIS;Y-AXIS", &TargetMovementMode_, bTargetMovementEdit_))
		{
			bTargetMovementEdit_ = !bTargetMovementEdit_;
		}
	}

	// Behavior select dropdown box.
	{
		if (GuiDropdownBox(Rectangle{AnchorTopRight.x - 230, AnchorTopRight.y + 100, 210, 50}, "SEEK;FLEE;INTERCEPT", &BehaviorValue_, bBehaviorDropdownEdit_))
		{
			bBehaviorDropdownEdit_ = !bBehaviorDropdownEdit_;
		}
	}
}
