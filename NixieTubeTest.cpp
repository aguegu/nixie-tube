/* Basic sample code for VFD-tube module for Arduino
 *
 * licensed under Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)
 * http://creativecommons.org/licenses/by-nc/3.0/
 *
 * Library Author: Weihong Guan (aGuegu)
 * Blog: http://aguegu.net
 * Email: weihong.guan@gmail.com
 *
 * VFD moudle for Arduino
 *
 *              /----------------------------\
 *              |                            |
 *              |                            |
 *              |                            |
 *              \----------------------------/
 *               |                          |
 * ------------------------------------------------
 * | 5V | 5V | GND | GND | DIN | OE | STCP | SHCP |
 * ------------------------------------------------
 *
 * Two pairs of 5v/GND
 * one could be used for power in from external power source
 * the other one could be used as fower for Arduino
 */

#include "NixieTubeTest.h"
#include "VFDTube.h"

VFDTube tube(8, 9, 10, 11, 6);
// DIN on pin #8, OE on pin #9, STCP on pin #10, SHCP on pin #11,
// 6 for sections count in serial

void setup()
{
	// set background led color individually
	for (byte i = 0; i < 6; i++)
		tube.setBackgroundColor(i, Color(i));

	// display "012345" for 3 seconds
	tube.printf("012345");
	tube.display(); // send data to modules
	delay(3000);

	// display " clock" for 3 seconds
	tube.printf(" clock");
	tube.display();
	delay(3000);

	// set background led color of all sections to green
	// display " with" for 3 seconds
	tube.setBackgroundColor(Green);
	tube.printf(" with");
	tube.display();
	delay(3000);

	// display "aGuegu" for 3 seconds
	tube.printf("aGuegu");
	tube.display();
	delay(3000);

	// no display for 2 seconds
	tube.clear();
	tube.display();
	delay(2000);

	// set background led color of all sections to blue
	// display "VFD .22" for 3 seconds
	tube.setBackgroundColor(Blue);
	tube.printf("VFD .22");
	tube.display();
	delay(3000);
}

// display a basic digital clock pattern

void loop()
{
	static byte s = 56; // second
	static byte m = 34; // minute
	static byte h = 12; // hour

	tube.clear();

	tube.setBackgroundColor((Color) ((s) / 7));
	// background color shift in every 7 seconds

	if (s & 0x01)
		tube.printf("%02d.%02d.%02d", h, m, s);
	else
		tube.printf("%02d%02d%02d", h, m, s);

	tube.display();
	delay(1000);	// reduce this value to check a fast shifting

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

