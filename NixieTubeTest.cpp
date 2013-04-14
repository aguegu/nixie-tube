#include "NixieTubeTest.h"

#include "tubetrain.h"

TubeTrain tt(4, 7, 6, 5);

void setup() {

}

void loop() {
	static word i = 0x01;
	tt.display(i);
	delay(200);

	i <<= 1;
	if (!i)
		i = 0x01;
}
