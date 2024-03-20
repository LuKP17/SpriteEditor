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
	uiButton *clearButton;
	
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
		
		clearButton = new uiButton(this, "Clear Sprite", Point(10, 100), Size(100, 20));
		clearButton->onClick = [&]() { onClearButtonClick(); };
	}

	void onClearButtonClick()
	{
		spriteGridFrame->clear();
		spriteGridFrame->repaint();
	}
};
