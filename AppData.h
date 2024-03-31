#pragma once

#include "fabgl.h"
#include "fabui.h"
#include "displaycontroller.h"

#define SPRITE_SIZE 16 // number of both rows and columns

struct AppData
{
	char *spriteName;
	uint8_t spriteSize;
	uint8_t cellSize;
	uint8_t bitmapData[SPRITE_SIZE][SPRITE_SIZE];
	Bitmap *spriteBitmap;
	RGB888 activeCol;

	AppData()
	{
		this->spriteName = "unnamed";
		this->spriteSize = SPRITE_SIZE;
		this->cellSize = 480 / SPRITE_SIZE;
		this->activeCol = Color::BrightWhite;
		this->spriteBitmap = new Bitmap(SPRITE_SIZE, SPRITE_SIZE, bitmapData, PixelFormat::RGBA2222);
		initSprite();
	}

	void initSprite(void)
	{
		for (int i = 0; i < spriteSize; i++) {
			for (int j = 0; j < spriteSize; j++) {
				spriteBitmap->setPixel(i, j, RGBA2222(255, 255, 255, 255));
			}
		}
	}
};
