#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

struct SpriteGridFrame : public uiFrame
{
	AppData *appData;

	SpriteGridFrame(uiFrame * parent, AppData *appData)
	: uiFrame(parent, "", Point(0, 0), Size(480, 480), true)
	{
		frameStyle().backgroundColor = RGB888(255, 255, 255);
		windowStyle().borderSize	 = 0;
		frameProps().resizeable		 = false;
		this->appData = appData;

		// draw sprite
		canvas()->drawBitmap(0, 0, appData->spriteBitmap);
	}

	void clear()
	{
	}
};
