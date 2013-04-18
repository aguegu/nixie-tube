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

	tt.printf("%02d", c);

//	((Iv22 &)(tt.getTube(1))).setChar(c);
//	//tt.getTube(1).setChar(c);
//	((Iv22 &)(tt.getTube(0))).setChar('0' + 9 - (c - '0'));

	tt.display();
	delay(0x20);
	x++;

	if (!(x & 0x1f)) {
		c++;
	}
}
