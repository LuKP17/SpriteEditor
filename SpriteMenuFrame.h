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

		titleLabel = new uiLabel(this, "Sprite Editor", Point(5,  10), Size(115, 20));
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
		SerialBT.printf("P3 %d %d 255\n", appData->spriteSize, appData->spriteSize);

		uint8_t rgb[3];
		for (int i = 0; i < appData->spriteSize; i++) {
			for (int j = 0; j < appData->spriteSize; j++) {				
				rgb[0] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].R;
				rgb[1] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].G;
				rgb[2] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].B;
				for (int c = 0; c < 3; c++) {
					if (rgb[c] == 3) rgb[c] = 255;
				}
				SerialBT.printf("%d %d %d ", rgb[0], rgb[1], rgb[2]);
			}
		}

		SerialBT.println();
	}

	void onExportConsoleButtonClick()
	{
		Serial.printf("P3 %d %d 255\n", appData->spriteSize, appData->spriteSize);

		uint8_t rgb[3];
		for (int i = 0; i < appData->spriteSize; i++) {
			for (int j = 0; j < appData->spriteSize; j++) {				
				rgb[0] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].R;
				rgb[1] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].G;
				rgb[2] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].B;
				for (int c = 0; c < 3; c++) {
					if (rgb[c] == 3) rgb[c] = 255;
				}
				Serial.printf("%d %d %d ", rgb[0], rgb[1], rgb[2]);
			}
		}
	}

	void onClearButtonClick()
	{
		appData->initSprite();
		spriteGridFrame->repaint();
	}
};