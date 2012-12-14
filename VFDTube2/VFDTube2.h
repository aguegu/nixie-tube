/*
 * VFDTube2.h
 *
 *  Created on: Dec 3, 2012
 *      Author: agu
 */

#ifndef VFDTUBE2_H_
#define VFDTUBE2_H_

#include "Arduino.h"

enum Color
{
	White, Yellow, Magenta, Red, Cyan, Green, Blue, Black,
};

const uint8_t PROGMEM VFDTUBE2_FONT[] PROGMEM =
{
		0xde, 0x48, 0x9b, 0xcb, 0x4d,
		0xc7, 0xd7, 0x4a, 0xdf, 0xcf,

		0xdb, 0xd5, 0x91, 0xd9, 0x9f,
		0x17, 0xd6, 0x55, 0x14, 0xc8,
		0x95, 0x94, 0x5e, 0x51, 0xd1,
		0x1f, 0x4f, 0x11, 0x45, 0x15,
		0xd0, 0x90, 0x0d, 0x0f, 0x49, 0x19,
};

class VFDTube2
{
public:

	VFDTube2(uint8_t pin_din, uint8_t pin_oe, uint8_t pin_st, uint8_t pin_sh,
			byte section_count);

	virtual ~VFDTube2();

	void display();

	void putWord(byte index, word value = 0xff00);
	void clear(word value = 0xff00);

	void setBackgroundColor(Color color);
	void setBackgroundColor(byte index, Color color);

	void setBrightness(byte brightness = 0xff);

	void setPoint(byte index);
	bool setChar(byte index, char c);
	void setChar(char c);

	void printf(const char *__fmt, ...);

private:

	word *_buff;

	const uint8_t _pin_din; // DIN
	const uint8_t _pin_oe; // OE, pin with PWM output is recommended to enable brightness adjustment
	const uint8_t _pin_st; // STCP
	const uint8_t _pin_sh; // SHCP

	const byte _section_count;

	void send(byte data) const;
	bool displayable(char c);

};

#endif /* VFDTUBE2_H_ */
