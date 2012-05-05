#include "NixieTubeTest.h"
#include "NixieTube.h"

NixieTube tube(11, 12, 13, 10, 4);

void setup()
{
	//tube.setBackgroundColor(Blue);
}

void loop()
{
	long k = random();

	tube.setBackgroundColor((Color)(k%8));
	tube.setColon((Colon)(k%4));

	tube.putNumber(k, 4);

	tube.display();
	delay(1000);
}
