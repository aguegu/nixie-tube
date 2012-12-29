#include "NixieTubeTest.h"
#include "Sig16.h"

#define TUBE_COUNT 1

Sig16 tube(11, 9, 10, 8, TUBE_COUNT);

word PATTERN16[] =
{
// 0x7cf4, 0x0060, 0xd8b8, 0xc8f8, 0xa068, 0xe990, 0xf8d8, 0x4070, 0xf8f8, 0xe8f8
		0x0d80, 0x0202, 0x4c94, 0x4994, 0x0cc4, 0x4991, 0x0d84, 0x4414, 0x4d95, 0x4415
};

void setup()
{

}

void loop()
{
	for (byte i = 0; i < sizeof(PATTERN16) >> 1; i++)
	{
		tube.send(PATTERN16[i]);
		tube.display();
		delay(500);
	}

}

