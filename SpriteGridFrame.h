#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

// SIMPLIFIED FOR TESTING MORE IMPORTANT STUFF, BUT A LOT OF MEMORY WASTED!
#define MAX_GRID_SIZE 16

struct SpriteGridFrame : public uiFrame
{
	AppData *appData;
	uint16_t gridButtonSize;
	uiButton *gridButtons[MAX_GRID_SIZE][MAX_GRID_SIZE];

	SpriteGridFrame(uiFrame * parent, AppData *appData)
	: uiFrame(parent, "", Point(0, 0), Size(480, 480), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize	 = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;
		gridButtonSize = 480 / appData->gridSize;
		for (int i = 0; i < appData->gridSize; i++) {
			for (int j = 0; j < appData->gridSize; j++) {
				gridButtons[i][j] = new uiButton(
					this,
					"",
					Point(i*gridButtonSize, j*gridButtonSize),
					Size(gridButtonSize, gridButtonSize)
				);
				gridButtons[i][j]->buttonStyle().backgroundColor = Color::BrightWhite;
				gridButtons[i][j]->buttonStyle().downBackgroundColor = Color::BrightWhite;
				gridButtons[i][j]->buttonStyle().mouseDownBackgroundColor = Color::BrightWhite;
				gridButtons[i][j]->buttonStyle().mouseOverBackgroundColor = Color::BrightWhite;
				gridButtons[i][j]->onClick = [&]() { onGridButtonClick(); };
			}
		}
	}

	void onGridButtonClick() {
		MouseStatus mouseStatus = app()->mouse()->status();
		int i = mouseStatus.X / gridButtonSize;
		int j = mouseStatus.Y / gridButtonSize;
		gridButtons[i][j]->buttonStyle().backgroundColor = appData->activeCol;
	}

	void clear()
	{
		for (int i = 0; i < appData->gridSize; i++) {
			for (int j = 0; j < appData->gridSize; j++) {
				gridButtons[i][j]->buttonStyle().backgroundColor = Color::BrightWhite;
			}
		}
	}
};
