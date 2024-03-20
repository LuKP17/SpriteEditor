#pragma once

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"

#define GRID_SIZE 32

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

		paintBox = new uiPaintBox(this, clientPos(), clientSize());
		paintBox->anchors().right = true;
		paintBox->anchors().bottom = true;
		paintBox->onPaint = [&](Rect const & r) { onPaintPaintBox(r); };

		paintBox->repaint(); // TEST I guess this calls onPaintPaintBox()

		this->appData = appData;
	}

	void onPaintPaintBox(Rect const & r)
	{
		/* Perform custom drawings */

		int w = r.width(), h = r.height();

		auto cv = canvas();

		// TEST I hope the sprite grid will be red
		cv->setPenColor(Color::BrightRed);
		cv->fillRectangle(r)
	}

	void clear()
	{
		return;
	}
};
