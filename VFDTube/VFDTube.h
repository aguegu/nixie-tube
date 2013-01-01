/*
 * VFDTube.h
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#ifndef VFDTUBE_H_
#define VFDTUBE_H_

#include "Arduino.h"

enum Color
{
	White, Yellow, Magenta, Red, Cyan, Green, Blue, Black,
};

const uint8_t PROGMEM VFDTUBE_FONT[] =
{
	// 0-9
	0xb7, 0x22, 0x9b, 0xab, 0x2e, 0xad, 0xbd, 0x23, 0xbf, 0xaf,

	// a-z
	0xbb, 0xbc, 0x98, 0xba, 0x9f, 0x1d, 0xb5, 0x3c, 0x14, 0xa2, 0x9c, 0x94,
	0x37, 0x38, 0xb8, 0x1f, 0x2f, 0x18, 0x2c, 0x1c, 0xb0, 0x90, 0x0e, 0x0f,
	0x2a, 0x1a,
};

class VFDTube
{
public:

	VFDTube(uint8_t pin_din, uint8_t pin_oe, uint8_t pin_st, uint8_t pin_sh,
			byte section_count);
	virtual ~VFDTube();

	void display();
	void display(word milis);

	void putWord(byte index, word value = 0xff00);
	void clear(word value = 0xff00);

	void setBackgroundColor(Color color);
	void setBackgroundColor(byte index, Color color);

	void setBrightness(byte brightness = 0xff);

	void setPoint(byte index);
	void setPattern(byte index, byte pattern);
	byte getPattern(byte index);

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

#endif /* VFDTUBE_H_ */
