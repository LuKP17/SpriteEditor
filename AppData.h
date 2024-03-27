#pragma once

#include "fabgl.h"
#include "fabui.h"

#define SPRITE_SIZE 16 // number of both rows and columns

struct AppData
{
	char *spriteName;
	const uint8_t bitmapData[SPRITE_SIZE][SPRITE_SIZE];
	Bitmap *spriteBitmap;
	RGB888 activeCol;

	AppData()
	{
		this->spriteName = "unnamed";
		this->activeCol = Color::BrightWhite;
		// Bitmap
		// A bitmap is a rectangular image with one byte per pixel.
		// Each pixel has up to 64 colors (2 bits per channel) and can have 4 level of transparency.
		// At the moment only level 0 (full transparent) and level 3 (full opaque) is supported.

		// RGBA2222
		// 8 bit per pixel: AABBGGRR (bit 7=A 6=A 5=B 4=B 3=G 2=G 1=R 0=R)
		// AA = 0 fully transparent, AA = 3 fully opaque.
		// Each color channel can have values from 0 to 3 (maxmum intensity)
		this->spriteBitmap = new Bitmap(SPRITE_SIZE, SPRITE_SIZE, bitmapData, RGBA2222)
		// I want red as the initial bitmap,
		// With blue in the middle row,
		// With green in the center
		for (int i = 0; i < SPRITE_SIZE; i++) {
			for (int j = 0; j < SPRITE_SIZE; j++) {
				if (i == SPRITE_SIZE / 2)
					spriteBitmap->setPixel(i, j, RGBA2222(0, 0, 255, 255));
				if (i == SPRITE_SIZE / 2 && j == SPRITE_SIZE / 2)
					spriteBitmap->setPixel(i, j, RGBA2222(0, 255, 0, 255));
				else
					spriteBitmap->setPixel(i, j, RGBA2222(255, 0, 0, 255));
			}
		}
	}
};
