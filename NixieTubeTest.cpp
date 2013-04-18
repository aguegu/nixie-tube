#include "NixieTubeTest.h"

#include "tubetrain.h"

TubeTrain tt(4, 7, 6, 5, 2);

void setup() {
	tt.initTube(0, new Iv22());
	tt.initTube(1, new Iv22());
	((Iv22 &)(tt.getTube(0))).setEffectEnable(true);
	((Iv22 &)(tt.getTube(1))).setEffectEnable(true);
}

void loop() {
	static byte c = 0;
	static byte x = 0;

	// update content every 0x20 units
	if (!(x & 0x1f)) {
		tt.printf("%02d", c);

		tt.setPoint(0, c & 0x01);
		((Iv22 &)(tt.getTube(0))).setColor(Tube::Red);

		c++;
		c %= 100;
	}

	tt.display();
	delay(0x20);
	x++;
}
