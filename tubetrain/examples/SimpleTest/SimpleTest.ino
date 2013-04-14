#include "VFDTube.h"

#define TUBE_COUNT 1

VFDTube tube(4, 5, 6, 7, TUBE_COUNT);
// DIN on pin #4, OE on pin #5, STCP on pin #6, SHCP on pin #7,
// TUBE_COUNT stands for sections count in serial
// Pin #5 is with PWM output on UNO, so the brightness is adjustable

void setup() {
	tube.setBrightness(0x20); // set brightness, range 0x00 - 0xff
}

// display a basic digital clock pattern
void loop() {
	for (byte i = 0; i < 16; i++) {
		tube.setSection(0, _BV(i));
		tube.display();
		delay(1000);
	}
}
