#pragma once

#include "fabui.h"

#include "AppData.h"
#include "SpriteGridFrame.h"

struct SpriteMenuFrame : public uiFrame
{
	AppData *appData;
	SpriteGridFrame *spriteGridFrame;
	uiLabel *titleLabel;
	uiTextEdit *spriteNameEdit;
	uiButton *exportButton, *clearButton;
	
	SpriteMenuFrame(uiFrame * parent, AppData *appData, SpriteGridFrame *spriteGridFrame)
	: uiFrame(parent, "", Point(480, 160), Size(160, 320), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize     = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;
		this->spriteGridFrame = spriteGridFrame;

		titleLabel = new uiLabel(this, "Sprite Editor", Point(10,  33), Size(150, 20));
		titleLabel->labelStyle().backgroundColor = frameStyle().backgroundColor;
		titleLabel->labelStyle().textFont = &fabgl::FONT_std_24;
		titleLabel->update();
		
		exportButton = new uiButton(this, "Export Sprite", Point(10, 100), Size(100, 20));
		exportButton->onClick = [&]() { onExportButtonClick(); };
		clearButton = new uiButton(this, "Clear Sprite", Point(10, 150), Size(100, 20));
		clearButton->onClick = [&]() { onClearButtonClick(); };
	}

	void onExportButtonClick()
	{
		SerialBT.write("abcd", 4); // TEST "abcd" should be printed on my phone

		// Now let's send the hardcoded string of a .pbm file to visualize the sprite in GIMP.
		// Possible for the contents to be stored in a single line.
		// But might be easier in code to send the data by value.

		// BEGIN FILE
		// P3 SPRITE_SIZE SPRITE_SIZE 255
		// R G B (uint_8t, uint8_t, uint8_t)
		// R G B
		// ...
		// R G B
		// END FILE
		Serial.write("P3 4 4 255 0 0 0 255 0 0 0 255 0 255 255 0 0 0 255 255 0 255 0 255 255 255 255 255 0 0 0 255 0 0 0 255 0 255 255 0 0 0 255 255 0 255 0 255 255 255 255 255", 154);
	}

	void onClearButtonClick()
	{
		spriteGridFrame->clear();
		spriteGridFrame->repaint();
	}
};
