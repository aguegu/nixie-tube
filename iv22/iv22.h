/*
 * Iv22.h
 *
 *  Created on: Apr 15, 2013
 *      Author: agu
 */

#ifndef IV22_H_
#define IV22_H_

#include "Arduino.h"
#include "tube.h"

static const byte PROGMEM VFDTUBE_FONT[] = {
		// 0-9
		0xb7, 0x22, 0x9b, 0xab, 0x2e, 0xad, 0xbd, 0x23, 0xbf, 0xaf,

		// a-z
		0xbb, 0xbc, 0x98, 0xba, 0x9f, 0x1d, 0xb5, 0x3c, 0x14, 0xa2, 0x9c, 0x94,
		0x37, 0x38, 0xb8, 0x1f, 0x2f, 0x18, 0x2c, 0x1c, 0xb0, 0x90, 0x0e, 0x0f,
		0x2a, 0x1a, };

class Iv22: public Tube {

public:
	enum Color {
		White, Yellow, Magenta, Red, Cyan, Green, Blue, Black,
	};

	Iv22();
	virtual ~Iv22();
	void setValue(word value = 0xff00);
	void setBackgroundColor(Color color);

	void setPatternTo(byte pattern);

	void setPoint(bool on);
	bool setChar(char c);
	byte getPattern(void);

	void transform();
	byte getBuffLength();

private:

	static const byte _BUFF_LENGTH = 2;

	bool isDisplayable(char c);
	byte _frame;
	byte _pattern_from, _pattern_to;
	void setPattern(byte pattern);

	void (Iv22::*_transform_effect)();

	void transformBlink();
	void transformRoll();
	void transformSlip();
	void transformType();

	byte getPatternIndex(byte pattern);
};

#endif /* IV22_H_ */
