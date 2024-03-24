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

		/* WORKS, THE PAINTBOX IS DRAWN AT THE RIGHT POS/SIZE */
		paintBox = new uiPaintBox(this, clientPos(), clientSize());
		paintBox->anchors().right = true;
		paintBox->anchors().bottom = true;

		// called when making another frame active, then also when making the grid frame active, and when clicking on Clear button
		// IT'S FINE, BUT I WANT TO CALL IT WHEN THE USER CLICKS IN THE FRAME
		paintBox->onPaint = [&](Rect const & r) { onPaintPaintBox(r); };

		this->appData = appData;
	}

	void onPaintPaintBox(Rect const & r)
	{
		Serial.printf("Entered custom paint function\n");
		/* Perform custom drawings */
		// DOESN'T DRAW SHIT

		int w = r.width(), h = r.height();

		auto cv = canvas();

		// TEST I hope the sprite grid will be red
		cv->setPenColor(Color::BrightGreen);
		cv->fillRectangle(r);
	}

	void clear()
	{
		return;
	}
};
