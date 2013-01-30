/*
 * SimpleClock.cpp
 *
 *  Created on: 2012-9-5
 *      Author: agu
 */
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

#include "NixieTube.h"

#define COUNT	8
// define how many modules in serial

NixieTube tube(11, 12, 13, 10, COUNT);
// pin_ds, pin_st. pin_sh, pin_oe(pwm pin is preferred), COUNT

void setup()
{
	for(byte i=0; i<COUNT; i++)
	{
		tube.setBackgroundColor(i, (Color)(i%8));	// set different background color for each module
//		tube.setColon(i, (Colon)(i%4));
//		tube.setNumber(i, i);
	}

	tube.setBrightness(0xff);	// brightness control, 0x00(off)-0xff

	tube.display();
}

void loop()
{
	static byte h = 0, m = 0, s = 0, cs = 0;

	tube.printf("%02d:%02d:%02d'%02d", h, m, s, cs);

	tube.display();
	delay(10);
	cs++;
	if (cs == 100) {cs=0; s++;}
	if (s == 60) {s=0; m++;}
	if (m == 60) {m=0; h++;}
	if (h == 24) {h=0;}

}
