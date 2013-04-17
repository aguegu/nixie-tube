#include "NixieTubeTest.h"

#include "tubetrain.h"

TubeTrain tt(4, 7, 6, 5, 2);

void setup() {
	tt.initTube(0, new Iv22());
	tt.initTube(1, new Iv22());
	((Iv22 &)(tt.getTube(0))).setChar('6');
}

void loop() {
	static char c = '0';
	static byte x = 0;

	((Iv22 &)(tt.getTube(1))).setChar(c);
	//tt.getTube(1).setChar(c);
	//tt.getTube(1).setChar('0' + 9 - (c - '0'));

	tt.display();
	delay(0x20);
	x++;

	if (!(x & 0x1f)) {
		c++;
		if (c > '9')
			c = '0';
	}
}
