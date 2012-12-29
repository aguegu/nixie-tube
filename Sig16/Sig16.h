/*
 * Sig16.h
 *
 *  Created on: Dec 21, 2012
 *      Author: agu
 */

#ifndef SIG16_H_
#define SIG16_H_

#include "Arduino.h"

class Sig16
{
public:
	Sig16(uint8_t pin_din, uint8_t pin_st, uint8_t pin_sh, uint8_t pin_oe,
			byte section_count = 1);
	virtual ~Sig16();
	void send(word data) const;
	void display() const;
private:
	const uint8_t _pin_dt;
	const uint8_t _pin_st;
	const uint8_t _pin_sh;
	const uint8_t _pin_oe;
	const byte _section_count;
};

#endif /* SIG16_H_ */
