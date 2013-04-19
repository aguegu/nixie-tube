#include "NixieTubeTest.h"

#include "tubetrain.h"
#include "iv22.h"
#include "iv17.h"

void update();

TubeTrain tt(4, 6, 7, 5, 1);

void setup() {
	tt.initTube(0, new Iv17());
}

void loop() {
	static byte t = 0;

	// update content every 0x20 units
	if (!(t & 0x1f)) {
		update();
	}

	tt.display();
	delay(0x20);
	t++;
}

byte start = 'A';

void update() {
	static byte c = start;

	//tt.getTube(0).setBuff((byte[]){0,0,  (byte)(0x01<<c)}, 3);

//		tt.printf("%02d", c);
//		tt.setPoint(0, c & 0x01);
//		((Iv22 &)(tt.getTube(0))).setColor((Tube::Color)(c & 0x07));

	//tt.setPoint(0, c & 0x03);
	tt.setChar(0, c + 10 - 'A');
	c++;
	if (c > 'Z')
		c = start;

}
