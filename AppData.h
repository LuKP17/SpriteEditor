#pragma once

#include "fabgl.h"
#include "fabui.h"

struct AppData
{
	char *spriteName;
	RGB888 activeCol;

	AppData()
	{
		this->spriteName = "unnamed";
		this->activeCol = Color::BrightWhite;
	}
};
