#include "NixieTubeTest.h"
#include "NixieTube.h"

NixieTube tube(11, 12, 13, 10);

void setup()
{

}

void loop()
{
	for (byte i = 0; i < 8; i++)
	{
		tube.putByte(0x40, _BV(i));
		delay(500);
	}

	for (byte i = 0; i < 8; i++)
	{
		tube.putByte(_BV(i), 0x00);
		delay(500);
	}
}
