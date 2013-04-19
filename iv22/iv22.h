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

class Iv22: public Tube {

public:

	Iv22();
	virtual ~Iv22();
	void setValue(word value = 0xff00);
	void setColor(Tube::Color color);

	void setPatternDest(byte pattern);
	void setPatternCurrent(byte pattern);
	byte getPatternCurrent(void);

	void setPoint(byte on);
	void setChar(char c);
	void setEffectEnable(bool);

	void runEffect(void);
	byte getBuffLength(void);

private:
	static const byte _BUFF_LENGTH = 2;

	byte convertCharToIndex(char c);
	byte _frame;
	byte _pattern_from, _pattern_to;
	bool _effect_enable;

	void (Iv22::*_effect)();

	void effectBlink();
	void effectRoll();
	void effectSlip();
	void effectStroke();

	byte getPatternIndex(byte pattern);
};

#endif /* IV22_H_ */
