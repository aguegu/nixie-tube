#include "NixieTubeTest.h"
#include "NixieTube.h"

NixieTube tube(11, 12, 13, 10, 5);

void setup()
{
	//tube.setBackgroundColor(Blue);

}

void loop()
{
	static word k = 0;
	tube.setBackgroundColor((Color)(k%8));
	tube.putNumber(k++,1);
	tube.display();
	delay(1000);
}
