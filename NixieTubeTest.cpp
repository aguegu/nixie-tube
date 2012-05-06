#include "NixieTubeTest.h"
#include "NixieTube.h"

NixieTube tube(11, 12, 13, 10, 10);

void setup()
{
	tube.setBrightness(0xf0);

	for(byte i=0; i<10; i++)
	{
		tube.setBackgroundColor(i, (Color)(i%8));
		tube.setColon(i, (Colon)(i%4));
		tube.setNumber(i, i);
	}
	tube.display();
}

void loop()
{
	delay(1000);
	tube.display();
}
