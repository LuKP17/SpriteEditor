/*
	SpriteEditor (M1 TER Project)

	Click with a mouse on a grid with the color selected from a limited palette.
	If time, save the sprite in a .json file and send it via Bluetooth or Wi-Fi.
*/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#include "fabgl.h"
#include "fabui.h"

#include "AppData.h"
#include "SpriteGridFrame.h"
#include "ColorPaletteFrame.h"
#include "SpriteMenuFrame.h"

fabgl::VGA16Controller DisplayController;
fabgl::Canvas cv(&DisplayController);
fabgl::PS2Controller PS2Controller;

class MyApp : public uiApp
{
	AppData *appData;
	SpriteGridFrame *spriteGridFrame;
	ColorPaletteFrame *colorPaletteFrame;
	SpriteMenuFrame *spriteMenuFrame;

	fabgl::Stack<uiFrame*> dynamicFrames;

	void init()
	{
		PS2Controller.mouse()->setupAbsolutePositioner(cv.getWidth(), cv.getHeight(), true, &DisplayController, this);
		rootWindow()->frameStyle().backgroundColor = RGB888(255, 255, 255);

		// init app data
		appData = new AppData();

		// sprite grid frame
		spriteGridFrame = new SpriteGridFrame(rootWindow(), appData);

		// color palette frame
		colorPaletteFrame = new ColorPaletteFrame(rootWindow(), appData);

		// sprite menu frame
		spriteMenuFrame = new SpriteMenuFrame(rootWindow(), appData, spriteGridFrame);
  }
};


void setup()
{
	Serial.begin(115200);
	SerialBT.begin("ESP32-BT-Slave"); //Bluetooth device name
	delay(500);  // avoid garbage into the UART
	Serial.write("\n\nReset\n");

	DisplayController.begin();
	DisplayController.setResolution(VGA_320x200_70Hz);

	PS2Controller.begin(PS2Preset::MousePort1);
	Serial.printf("Screen size: (%d, %d)\n", cv.getWidth(), cv.getHeight());
}

void loop()
{
	MyApp().runAsync(&DisplayController, 3500).joinAsyncRun(); // why this? Just to use a larger stack!
}
