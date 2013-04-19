/*
 * Iv17.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: agu
 */

#include "iv17.h"

/*
 * 		--- ---			6		c
 * 		|\ | /|		5	8	9	a	d
 * 		| \|/ |
 * 		--- ---			7		b
 * 		| /|\ |
 * 		|/ | \|		4	2	1	0	e
 * 		--- ---		  	3		f
 *
 *		7:	left dot
 *		6:	right dot
 *		5:	green
 *		4:	red
 *		3:	blue
 *		2-0: null
 */

static const byte PROGMEM IV17_FONT[] = {
		// 0-9
		0x7c, 0xf4, 0x00, 0x60, 0xd8, 0xb8, 0xc8, 0xf8, 0xa0, 0x68, 0xe9, 0x90,
		0xf8, 0xd8, 0x40, 0x70, 0xf8, 0xf8, 0xe8, 0xf8,

		// a-z
		0xf0, 0x78, 0x4a, 0xfa, 0x78, 0x90, 0x4a, 0xf2, 0xf8, 0x98, 0xf0, 0x18,
		0x78, 0xd8, 0xb0, 0x68, 0x4a, 0x92, 0x18, 0xe0, 0xb1, 0x04, 0x38, 0x80,
		0x30, 0x65, 0x31, 0x61, 0x78, 0xf0, 0xf0, 0x38, 0x79, 0xf0, 0xf1, 0x38,
		0xe8, 0xd8, 0x42, 0x12, 0x38, 0xe0, 0x34, 0x04, 0x35, 0x60, 0x05, 0x05,
		0xa2, 0x28, 0x4c, 0x94, };

Iv17::Iv17() {
	_buff = (byte *) malloc(sizeof(byte) * _BUFF_LENGTH);
	_buff[0] = 0;
	_buff[1] = 0;
	_buff[2] = 0xf8;
}

Iv17::~Iv17() {
	free(_buff);
}

byte Iv17::getBuffLength() {
	return _BUFF_LENGTH;
}

void Iv17::setPoint(byte point) {
	_buff[2] |= 0xc0;
	_buff[2] ^= point << 6;
}

void Iv17::setChar(char c) {
	byte index = convertCharToIndex(c);

	if (index == 255)
		return;

	memcpy_P(_buff, IV17_FONT + (index << 1), 2);
}

byte Iv17::convertCharToIndex(char c) {
	byte index = 255;
	if (c >= '0' && c <= '9')
		index = c - '0';
	else if (c >= 'A' && c <= 'Z')
		index = c - 'A' + 10;
	else if (c >= 'a' && c <= 'z')
		index = c - 'a' + 10;
	return index;
}

static const uint8_t PROGMEM COLORS[] = { 0x07, 0x06, 0x03, 0x02, 0x05, 0x04,
		0x01, 0x00 };

void Iv17::setColor(Tube::Color color) {
	_buff[2] &= 0xc0;
	_buff[2] |= pgm_read_byte_near(COLORS + color) << 3;
}
