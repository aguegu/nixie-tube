#include "NixieTubeTest.h"
#include "NixieTube.h"

NixieTube tube(11, 12, 13, 10, 5);

void setup()
{
	//tube.setBackgroundColor(Blue);
}

void loop()
{
	long k = random(0, 100000);

	tube.setBackgroundColor((Color)(k%8));
	tube.setColon(k % 5, (Colon)(k%4));

	tube.putNumber(k,5);

	tube.display();
	delay(1000);
}
