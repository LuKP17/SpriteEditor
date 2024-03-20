#pragma once

#include "fabgl.h"
#include "fabui.h"

struct AppData
{
	int gridSize;
	char *spriteName;
	RGB888 activeCol;

	AppData()
	{
		this->gridSize = 16;
		this->spriteName = "unnamed";
		this->activeCol = Color::BrightWhite;
	}
};
