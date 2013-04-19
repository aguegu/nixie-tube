#include "NixieTubeTest.h"

#include "tubetrain.h"
#include "iv22.h"
#include "iv17.h"

void update();

TubeTrain tt(4, 6, 7, 5, 2);

void setup() {
	tt.initTube(0, new Iv17());
	tt.initTube(1, new Iv17());
//t.setColor(0, Tube::Cyan);
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

void update() {
	static byte c = 0;

	tt.printf("%02d", c++);

}
