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
	uiButton *exportBluetoothButton, *exportConsoleButton, *clearButton;
	
	SpriteMenuFrame(uiFrame * parent, AppData *appData, SpriteGridFrame *spriteGridFrame)
	: uiFrame(parent, "", Point(200, 40), Size(120, 280), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize     = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;
		this->spriteGridFrame = spriteGridFrame;

		titleLabel = new uiLabel(this, "Sprite Editor", Point(5,  33), Size(115, 20));
		titleLabel->labelStyle().backgroundColor = frameStyle().backgroundColor;
		titleLabel->labelStyle().textFont = &fabgl::FONT_std_22;
		titleLabel->update();
		
		exportBluetoothButton = new uiButton(this, "Export Bluetooth", Point(10, 60), Size(100, 20));
		exportBluetoothButton->onClick = [&]() { onExportBluetoothButtonClick(); };
		exportConsoleButton = new uiButton(this, "Export Console", Point(10, 90), Size(100, 20));
		exportConsoleButton->onClick = [&]() { onExportConsoleButtonClick(); };
		clearButton = new uiButton(this, "Clear Sprite", Point(10, 120), Size(100, 20));
		clearButton->onClick = [&]() { onClearButtonClick(); };
	}

	void onExportBluetoothButtonClick()
	{
		SerialBT.write((const uint8_t *)appData->spriteName, 7);
	}

	void onExportConsoleButtonClick()
	{
		// bunch of Serial.printf to avoid having big buffers
		Serial.printf("Hey hey!\n");
	}

	void onClearButtonClick()
	{
		appData->initSprite();
		spriteGridFrame->repaint();
	}
};