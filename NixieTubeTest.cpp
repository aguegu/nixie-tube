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
	tube.clear(0x300);
	tube.display();
}

void loop()
{
//	static byte val = 0x01;
//	tube.clear(val);
//	tube.display();
//
//	delay(1000);
//	val <<= 1;
//	if (val == 0) val = 0x01;
}

