#pragma once

#include "fabgl.h"
#include "fabui.h"
#include "displaycontroller.h"

#define SPRITE_SIZE 16 // number of both rows and columns

struct AppData
{
	char *spriteName;
	uint8_t bitmapData[SPRITE_SIZE][SPRITE_SIZE];
	Bitmap *spriteBitmap;
	RGB888 activeCol;

	AppData()
	{
		this->spriteName = "unnamed";
		this->activeCol = Color::BrightWhite;
		this->spriteBitmap = new Bitmap(SPRITE_SIZE, SPRITE_SIZE, bitmapData, PixelFormat::RGBA2222);
		for (int i = 0; i < SPRITE_SIZE; i++) {
			for (int j = 0; j < SPRITE_SIZE; j++) {
				if (j == SPRITE_SIZE / 2)
					spriteBitmap->setPixel(i, j, RGBA2222(0, 0, 255, 255));
				else
					spriteBitmap->setPixel(i, j, RGBA2222(255, 0, 0, 255));
				if (i == SPRITE_SIZE / 2 && j == SPRITE_SIZE / 2)
					spriteBitmap->setPixel(i, j, RGBA2222(0, 255, 0, 255));
			}
		}
	}
};
