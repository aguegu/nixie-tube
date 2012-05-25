#include "NixieTubeTest.h"
#include "NixieTube.h"

NixieTube tube(11, 12, 13, 10, 8);

void setup()
{
	tube.setBrightness(0xf0);
	tube.setBrightness();

	for(byte i=0; i<10; i++)
	{
		tube.setBackgroundColor(i, (Color)(i%8));
//		tube.setColon(i, (Colon)(i%4));
//		tube.setNumber(i, i);
	}

	tube.printf("912. :345");
	tube.putCache();

	tube.display();
}

void loop()
{
	static byte h = 0, m = 0, s = 0, cs = 0;

	tube.printf("%02d:%02d:%02d.%02d", h, m, s, cs);
	tube.putCache();
	tube.display();
	delay(10);
	cs++;
	if (cs == 100) {cs=0; s++;}
	if (s == 60) {s=0; m++;}
	if (m == 60) {m=0; h++;}
	if (h == 24) {h=0;}

}
