#include "NixieTubeTest.h"
#include "VFDTube.h"

#define TUBE_COUNT 4

VFDTube tube(8, 9, 10, 11, TUBE_COUNT);
// DIN on pin #8, OE on pin #9, STCP on pin #10, SHCP on pin #11,
// 6 for sections count in serial
// Pin #9 is with PWM output, so the brightness is adjustable

void setup()
{
	tube.setBrightness(0xc0); // set brightness, range 0x00 - 0xff
	tube.printf("%d", 2013);
	tube.setBackgroundColor(0, Green);
	tube.setBackgroundColor(1, Green);
	tube.setBackgroundColor(2, Blue);
	tube.setBackgroundColor(3, Blue);
	tube.display();
}

// display a basic digital clock pattern
void loop()
{
}

