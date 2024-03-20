#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

#define GRID_SIZE 16 // FIXME taille plus grande crash (probleme de memoire)

struct SpriteGridFrame : public uiFrame
{
	AppData *appData;
	RGB888 activeCol;
	uint16_t gridButtonSize;
	uiButton *gridButtons[GRID_SIZE][GRID_SIZE];

	SpriteGridFrame(uiFrame * parent, AppData *appData)
	: uiFrame(parent, "", Point(0, 0), Size(480, 480), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize	 = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;
		gridButtonSize = 480 / GRID_SIZE;
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
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
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
				gridButtons[i][j]->buttonStyle().backgroundColor = Color::BrightWhite;
			}
		}
	}
};
