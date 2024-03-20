/*
	SpriteEditor (M1 TER Project)

	Click with a mouse on a grid with the color selected from a limited palette.
	If time, save the sprite in a .json file and send it via Bluetooth or Wi-Fi.
*/

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"
#include "SpriteGridFrame.h"
#include "ColorPaletteFrame.h"
#include "SpriteMenuFrame.h"

fabgl::VGA16Controller DisplayController;
fabgl::PS2Controller PS2Controller;

/*
 * Improvements:
 *
 * - take arguments for the screen resolution to make the UI adapt to screen sizes
 *
*/
class MyApp : public uiApp
{
	AppData *appData;
	uiFrame *promptFrame;
	uiButton *size8Button, *size12Button, *size16Button;
	SpriteGridFrame *spriteGridFrame;
	ColorPaletteFrame *colorPaletteFrame;
	SpriteMenuFrame *spriteMenuFrame;

	// FIXME NON UTILISEE POUR L'INSTANT
	fabgl::Stack<uiFrame*> dynamicFrames;

	void init()
	{
		rootWindow()->frameStyle().backgroundColor = RGB888(255, 255, 255);

		// init app data
		appData = new AppData();

		// sprite grid frame
		spriteGridFrame = new SpriteGridFrame(rootWindow(), appData);

		// color palette frame
		colorPaletteFrame = new ColorPaletteFrame(rootWindow(), appData);

		// sprite menu frame
		spriteMenuFrame = new SpriteMenuFrame(rootWindow(), appData, spriteGridFrame);

		// prompt user for grid size
		promptFrame = new uiFrame(rootWindow(), "Grid Size", Point(100, 100), Size(200, 200));
    	promptFrame->frameStyle().backgroundColor = RGB888(255, 255, 255);
		size8Button = new uiButton(promptFrame, "8", Point(50, 100), Size(20, 20));
		size8Button->onClick = [&]() { onSize8ButtonClick(); };
		size12Button = new uiButton(promptFrame, "12", Point(100, 100), Size(20, 20));
		size12Button->onClick = [&]() { onSize12ButtonClick(); };
		size16Button = new uiButton(promptFrame, "16", Point(150, 100), Size(20, 20));
		size16Button->onClick = [&]() { onSize16ButtonClick(); };

		showWindow(promptFrame, true);
		setActiveWindow(promptFrame);
	}

	void onSize8ButtonClick()
	{
		appData->gridSize = 8;
		// showWindow(promptFrame, false);
		spriteGridFrame->repaint();
		destroyWindow(promptFrame);
	}

	void onSize12ButtonClick()
	{
		appData->gridSize = 12;
		// showWindow(promptFrame, false);
		spriteGridFrame->repaint();
		destroyWindow(promptFrame);
	}

	void onSize16ButtonClick()
	{
		appData->gridSize = 16;
		// showWindow(promptFrame, false);
		spriteGridFrame->repaint();
		destroyWindow(promptFrame);
	}
};


void setup()
{
	Serial.begin(115200);
	delay(500);  // avoid garbage into the UART
	Serial.write("\n\nReset\n");

	PS2Controller.begin(PS2Preset::MousePort1);

	DisplayController.begin();
	DisplayController.setResolution(VGA_640x480_60Hz);
}

void loop()
{
	MyApp().runAsync(&DisplayController, 3500).joinAsyncRun(); // why this? Just to use a larger stack!
}
