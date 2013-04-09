/*
 * Pt6311.h
 *
 *  Created on: Dec 13, 2012
 *      Author: agu
 */

#ifndef PT6311_H_
#define PT6311_H_

#include "Arduino.h"

#define CACHE_LENGTH 16
#define DIGIT_LENGTH 8

const uint16_t PROGMEM SIG14_FONT[] PROGMEM =
{
	0x5739, 0x0110, 0x52d1, 0x51d1, 0x41f0,
	0x58a1, 0x53e1, 0x0111, 0x53f1, 0x51f1,

	0x43f1, 0x5153, 0x1221, 0x5113, 0x52e1, 0x42e1,	// A-F
	0x1361, 0x43f0, 0x5003, 0x1310, 0x4aa8, 0x1220, // G-L

	0x433c, 0x4b34, 0x1331, 0x42f1, 0x1b31, 0x4af1, // M-R
	0x51e1, 0x4003, 0x1330, 0x4628, 0x4f30, 0x4c0c, // S-X
	0x5154, 0x5409	// Y-Z
};

class Pt6311
{
public:
	Pt6311(uint8_t pin_din, uint8_t pin_sck, uint8_t pin_stb);
	virtual ~Pt6311();
	void transmit(byte cmd);
	void init();
	void command(byte cmd);
	void display();
	void setBrightness(byte brightness = 0x05);
	void clear(byte val = 0x00);
	void setCache(byte index, byte val);
	void setDigit(byte index, word val);
	void setDigitChar(byte index, char chr);
	void printf(const char *__fmt, ...);
	void putDot(byte index);

private:
	const uint8_t _pin_din;
	const uint8_t _pin_sck;
	const uint8_t _pin_stb;
	byte * _cache;
	char * _str;

};

#endif /* PT6311_H_ */
