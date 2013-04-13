#include "VFDTube.h"

#define TUBE_COUNT 4

VFDTube tube(4, 5, 6, 7, TUBE_COUNT);
// DIN on pin #4, OE on pin #5, STCP on pin #6, SHCP on pin #7,
// TUBE_COUNT stands for sections count in serial
// Pin #5 is with PWM output on UNO, so the brightness is adjustable

void setup() {
	tube.setBrightness(0xf0); // set brightness, range 0x00 - 0xff
}

// display a basic digital clock pattern
void loop() {
	static byte s = 56; // second
	static byte m = 34; // minute

	tube.clear();
	// tube.setBackgroundColor(Red);
	tube.setBackgroundColor((Color) ((s) / 7));
	// background color shift in every 7 seconds

	if (s & 0x01)
		tube.printf("%02d.%02d.", m, s);
	else
		tube.printf("%02d%02d", m, s);

	//tube.setPoint(3);

	tube.display();
	delay(1000); // reduce this value to check a fast shifting

	s++;

	if (s == 60) {
		s = 0;
		m++;
	}

	if (m == 60)
		m = 0;
}

