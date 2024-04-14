#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

extern fabgl::PS2Controller PS2Controller;

struct SpriteGridFrame : public uiFrame
{
	AppData *appData;
	uiPaintBox *paintBox;

	SpriteGridFrame(uiFrame * parent, AppData *appData)
	: uiFrame(parent, "", Point(0, 0), Size(200, 200), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize	 = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;

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
		if (status.X > 0 && status.Y > 0 && status.X <= appData->spriteSize * appData->cellSize && status.Y <= appData->spriteSize * appData->cellSize) {
			// compute sprite pixel
			Serial.printf("Clicked registered at cell (%d, %d)\n", status.X / appData->cellSize, status.Y / appData->cellSize);
			// update bitmap
			appData->spriteBitmap->setPixel(status.X / appData->cellSize, status.Y / appData->cellSize, RGBA2222(appData->activeCol.R, appData->activeCol.G, appData->activeCol.B, 255));
		}
		repaintGrid();
	}

	/* FIXME: CAN JUST DRAW THE MODIFIED CELL! */
	void repaintGrid()
	{
		auto cv = canvas();

		// draw sprite
		uint8_t rgb[3];
		for (int i = 0; i < appData->spriteSize; i++) {
			for (int j = 0; j < appData->spriteSize; j++) {				
				rgb[0] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].R;
				rgb[1] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].G;
				rgb[2] = ((RGBA2222*)appData->spriteBitmap->data)[i * appData->spriteBitmap->width + j].B;
				for (int c = 0; c < 3; c++) {
					if (rgb[c] == 3) rgb[c] = 255;
				}
				cv->setBrushColor(rgb[0], rgb[1], rgb[2]);
				// required by low memory
				cv->fillRectangle(j * appData->cellSize, i * appData->cellSize, (j+1) * appData->cellSize, (i+1) * appData->cellSize);
			}
		}

		cv->setBrushColor(0, 0, 0);
		// draw horizontal grid lines
		for (int i = 0; i <= appData->spriteSize; i++) {
			cv->drawLine(0, i * appData->cellSize, appData->spriteSize * appData->cellSize, i * appData->cellSize);
		}
		// draw vertical grid lines
		for (int j = 0; j <= appData->spriteSize; j++) {
			cv->drawLine(j * appData->cellSize, 0, j * appData->cellSize, appData->spriteSize * appData->cellSize);
		}
		Serial.printf("Free 8bit: %d KiB\n", heap_caps_get_free_size(MALLOC_CAP_8BIT) / 1024);
		Serial.printf("Free 32bit: %d KiB\n", heap_caps_get_free_size(MALLOC_CAP_32BIT) / 1024);
	}
};
