#include "VFDTube.h"

#define TUBE_COUNT 1

VFDTube2 tube(8, 9, 10, 11, TUBE_COUNT);
// DIN on pin #8, OE on pin #9, STCP on pin #10, SHCP on pin #11,
// 6 for sections count in serial
// Pin #9 is with PWM output, so the brightness is adjustable

void setup()
{
	tube.setBrightness(0xFF); // set brightness, range 0x00 - 0xff

}

// display a basic digital clock pattern
void loop()
{
	for (byte i = 0; i < 16; i++)
	{
		tube.putWord(0, _BV(i));
		tube.display();
		delay(1000);
	}
}