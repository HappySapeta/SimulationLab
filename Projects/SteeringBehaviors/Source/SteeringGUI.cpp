#include "SteeringGUI.h"
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

constexpr int SceneGroupBoxWidth = 340;
constexpr int SceneGroupBoxHeight = 70;

constexpr int SceneDropBoxWidth = 210;
constexpr int SceneDropBoxHeight = 50;

void SteeringGUI::Draw()
{
	ClearBackground(LIGHTGRAY);

	// Scene selection box
	{
		GuiGroupBox(
			Rectangle
			{
				AnchorCenterBottom.x - SceneGroupBoxWidth / 2,
				AnchorCenterBottom.y - SceneGroupBoxHeight - 10,
				SceneGroupBoxWidth, SceneGroupBoxHeight
			},
			"CHOOSE SCENE");
	}

	{
		int DefaultTextSize = GuiGetStyle(DEFAULT, TEXT_SIZE);
		GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
		int DefaultAlignment = GuiGetStyle(TEXTBOX, TEXT_ALIGNMENT);
		GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
		
		GuiTextBox(Rectangle
			{
				AnchorCenterBottom.x - SceneDropBoxWidth / 2,
				AnchorCenterBottom.y - SceneDropBoxHeight - 20,
				SceneDropBoxWidth, SceneDropBoxHeight
			}, SceneNames.at(SceneIndex_), SCENE_TEXTSIZE, false);
		GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, DefaultAlignment);

		if(GuiButton(Rectangle
			{
				AnchorCenterBottom.x - SceneDropBoxWidth / 2 - 50 - 5,
				AnchorCenterBottom.y - SceneDropBoxHeight - 20,
				50, 50
			}, "<"))
		{
			SceneIndex_ = (SceneIndex_ - 1) % NUM_SCENES;
			if (SceneIndex_ < 0)
			{
				SceneIndex_ += NUM_SCENES;
			}
		}

		if (GuiButton(Rectangle
			{
				AnchorCenterBottom.x + SceneDropBoxWidth / 2 + 5,
				AnchorCenterBottom.y - SceneDropBoxHeight - 20,
				50, 50
			}, ">"))
		{
			SceneIndex_ = (SceneIndex_ + 1) % NUM_SCENES;
		}

		GuiSetStyle(DEFAULT, TEXT_SIZE, DefaultTextSize);
	}
}
