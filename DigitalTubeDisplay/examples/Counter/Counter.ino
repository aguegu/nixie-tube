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

#include "DigitalTubeDisplay.h"

//DigitalTubeDisplay dtd(6, 7, 8, 5, A5, A3, 10, 12, A2, A4, 9, 11);
uint8_t pin_digit[4] = {2, 11, 12, 9};
DigitalTubeDisplay dtd(pin_digit, 4, 3, 13, 10, 6, 5, 4, 8, 7);

void setup()
{

}

void loop()
{
	static byte s = 0, m=0;
	static char c = 'a';
	dtd.printf("%d.%d.%c", m, s, c++);

	dtd.display(0x40);

	s++;
	if (s==100)
	{
		s = 0;
		m++;
	}

	if (c=='z'+1) c='a';
}
