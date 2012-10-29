/* Basic sample code for digital-tube module for Arduino
 *
 * licensed under Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)
 * http://creativecommons.org/licenses/by-nc/3.0/
 *
 * Library Author: Weihong Guan (aGuegu)
 * Blog: http://aguegu.net
 * Email: weihong.guan@gmail.com
 *
 */

#include "NixieTubeTest.h"
#include "VFDTube.h"

VFDTube tube(8, 9, 10, 11, 6);

void setup()
{
	tube.clear();
	tube.printf(" nixie");
	tube.display();
	delay(3000);

	tube.clear();
	tube.printf(" clock");
	tube.display();
	delay(3000);

	tube.clear();
	tube.setBackgroundColor(Green);
	tube.printf(" with");
	tube.display();
	delay(3000);

	tube.clear();
	tube.printf("aGuegu");
	tube.display();
	delay(3000);

	tube.clear();
	tube.display();
	delay(2000);

	tube.clear();
	tube.setBackgroundColor(Blue);
	tube.printf("VFD. 22");
	tube.display();
	delay(3000);

	tube.clear();
}

void loop()
{
	static byte s = 56;
	static byte m = 34;
	static byte h = 12;

	tube.clear();
	tube.setBackgroundColor((Color) ((s) / 7));

	tube.printf("%02d.%02d.%02d", h, m, s);

	tube.display();

	delay(100);

	s++;

	if (s == 60)
	{
		s = 0;
		m++;
	}
	if (m == 60)
	{
		m = 0;
		h++;
	}
	if (h == 24)
	{
		h = 0;
	}
}

