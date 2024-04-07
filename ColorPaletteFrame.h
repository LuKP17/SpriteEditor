#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

#define NUM_COLORS 8
#define BUTTONS_PER_ROW 4

struct ColorPaletteFrame : public uiFrame
{
	AppData *appData;
	uint16_t paletteButtonSizeX, paletteButtonSizeY;
	uiButton *paletteButtons[NUM_COLORS / BUTTONS_PER_ROW][BUTTONS_PER_ROW];

	ColorPaletteFrame(uiFrame * parent, AppData *appData)
	: uiFrame(parent, "", Point(200, 0), Size(120, 40), true)
	{
		frameStyle().backgroundColor = RGB888(255, 0, 0);
		windowStyle().borderSize     = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;

		paletteButtonSizeX = 120 / BUTTONS_PER_ROW;
		paletteButtonSizeY = 40 / (NUM_COLORS / BUTTONS_PER_ROW);
		int colorNum;
		for (int i = 0; i < NUM_COLORS / BUTTONS_PER_ROW; i++) {
			for (int j = 0; j < BUTTONS_PER_ROW; j++) {
				paletteButtons[i][j] = new uiButton(
					this,
					"",
					Point(j*paletteButtonSizeX, i*paletteButtonSizeY),
					Size(paletteButtonSizeX, paletteButtonSizeY)
				);
				colorNum = i*BUTTONS_PER_ROW + j; // pick colors from enum class
				if (i != 0 || j != 0)
					colorNum = colorNum + 8; // choose "Bright..." colors except for black which isn't supported
				paletteButtons[i][j]->buttonStyle().backgroundColor = (Color)colorNum;
				paletteButtons[i][j]->buttonStyle().downBackgroundColor = Color::BrightWhite;
				paletteButtons[i][j]->buttonStyle().mouseDownBackgroundColor = Color::BrightWhite;
				paletteButtons[i][j]->buttonStyle().mouseOverBackgroundColor = (Color)colorNum;
				paletteButtons[i][j]->onClick = [&]() { onPaletteButtonClick(); };
			}
		}
	}

	void onPaletteButtonClick() {
		MouseStatus mouseStatus = app()->mouse()->status();
		int j = (mouseStatus.X - 200) / paletteButtonSizeX; // substract sprite grid size
		int i = mouseStatus.Y / paletteButtonSizeY;
		appData->activeCol = paletteButtons[i][j]->buttonStyle().backgroundColor;
	}
};
