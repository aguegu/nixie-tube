#include "NixieTubeTest.h"

#include "tubetrain.h"

TubeTrain tt(4, 7, 6, 5, 2);

void setup() {
	tt.getTube(0).setChar('6');
}

void loop() {
	static char c = '0';
	static byte x = 0;

	tt.getTube(1).setChar(c);
	//tt.getTube(1).setChar('0' + 9 - (c - '0'));

	tt.callAnimation();
	tt.display();
	delay(0x20);
	x++;

	if (!(x & 0x1f)) {
		c++;
		if (c > '9')
			c = '0';
	}
}
