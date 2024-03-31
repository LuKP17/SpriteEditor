#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

extern fabgl::Canvas cv;

struct SpriteGridFrame : public uiFrame
{
	AppData *appData;
	uiPaintBox *paintBox;

	SpriteGridFrame(uiFrame * parent, AppData *appData)
	: uiFrame(parent, "", Point(0, 0), Size(480, 480), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize	 = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;

		paintBox = new uiPaintBox(this, clientPos(), clientSize());
		paintBox->anchors().right = true;
		paintBox->anchors().bottom = true;
		paintBox->onPaint = [&](Rect const & r) { onPaintPaintBox(r); };
	}

	void onPaintPaintBox(Rect const & r) {
		cv.drawBitmap(10, 10, appData->spriteBitmap);
	}

	void clear()
	{
	}
};
