/* Basic sample code for nixie-tube module for Arduino
 *
 * licensed under Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)
 * http://creativecommons.org/licenses/by-nc/3.0/
 *
 * Hardware Designer: Yan Zeyuan
 * Blog: http://nixieclock.org
 * Email: yanzeyuan@163.com
 *
 * Library Author: Weihong Guan (aGuegu)
 * Blog: http://aguegu.net
 * Email: weihong.guan@gmail.com
 *
 * Pin Layout, right-side view, input from pins(male)
 *
 *              /-------------\
 *              |             |
 *              |             |
 *              |             |
 *              \-------------/
 *               |           |
 * -----------------------------
 * | SH  | ST  | DS  |
 * | 5V  | GND | OE  |
 * -------------------
 * | 12V | 12V | 12V |
 * | GND | GND | GND |
 * -----------------------------
 */

#include "NixieTubeTest.h"
#include "DigitalTubeDisplay.h"

//DigitalTubeDisplay dtd(6, 7, 8, 5, A5, A3, 10, 12, A2, A4, 9, 11);
DigitalTubeDisplay dtd;//(2, 11, 12, 9, 3, 13, 10, 6, 5, 4, 8, 7);

void setup()
{

}

void loop()
{
	static byte s = 0, m=0;
	dtd.printf("%2d.%02d", m, s);

	dtd.display(0x10);

	s++;
	if (s==100)
	{
		s = 0;
		m++;
	}
}
