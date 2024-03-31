#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

extern fabgl::PS2Controller PS2Controller;

struct SpriteGridFrame : public uiFrame
{
	AppData *appData;
	uiPaintBox *paintBox;
	uint16_t cellSize;

	SpriteGridFrame(uiFrame * parent, AppData *appData)
	: uiFrame(parent, "", Point(0, 0), Size(480, 480), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize	 = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;
		this->cellSize = 480 / appData->spriteSize;

		paintBox = new uiPaintBox(this, clientPos(), clientSize());
		paintBox->anchors().right = true;
		paintBox->anchors().bottom = true;
		paintBox->onPaint = [&](Rect const & r) {
			onPaintPaintBox(r);
		};
	}

	void onPaintPaintBox(Rect const & r) {
		// get mouse coordinates
		MouseStatus status;
		while (PS2Controller.mouse()->availableStatus()) {
			status = PS2Controller.mouse()->getNextStatus();
		}
		// check if mouse is inside this frame
		if (status.X <= 480 && status.Y <= 480) {
			// compute sprite pixel
			Serial.printf("Clicked registered at cell (%d, %d)\n", status.X / cellSize, status.Y / cellSize);
			// update bitmap
			appData->spriteBitmap->setPixel(status.X / cellSize, status.Y / cellSize, RGBA2222(appData->activeCol.R, appData->activeCol.G, appData->activeCol.B, 255));
		}
		repaintGrid();
	}

	void repaintGrid()
	{
		// draw sprite
		// USE DRAWRECTANGLES INSTEAD, NOT ENOUGH MEMORY FOR THE BITMAP TO TAKE THE WHOLE 480*480 GRID FRAME
		RGBA2222 col;
		auto cv = canvas();
		for (int i = 0; i < appData->spriteSize; i++) {
			for (int j = 0; j < appData->spriteSize; j++) {
				col = (RGBA2222)appData->bitmapData[i][j];
				cv->setBrushColor(RGB888(col.R, col.G, col.B));
				cv->fillRectangle(i * appData->cellSize, j * appData->cellSize, (i+1) * appData->cellSize, (j+1) * appData->cellSize);
			}
		}

		// draw grid on top
		// TODO
	}

	void clear()
	{
	}
};
