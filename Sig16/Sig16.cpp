/*
 * Sig16.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: agu
 */

#include "Sig16.h"

Sig16::Sig16(uint8_t pin_din, uint8_t pin_st, uint8_t pin_sh, uint8_t pin_oe,
		byte section_count) :
		_pin_dt(pin_din), _pin_st(pin_st), _pin_sh(pin_sh), _pin_oe(pin_oe), _section_count(
				section_count)
{
	pinMode(_pin_dt, OUTPUT);
	pinMode(_pin_st, OUTPUT);
	pinMode(_pin_sh, OUTPUT);
	pinMode(_pin_oe, OUTPUT);

	digitalWrite(_pin_oe, LOW);
	digitalWrite(_pin_st, LOW);
	digitalWrite(_pin_sh, LOW);
}

Sig16::~Sig16()
{

}

void Sig16::send(word data) const
{
	for (byte i = 0; i < 16; i++)
	{
		digitalWrite(_pin_dt, bitRead(data, 15-i));
		digitalWrite(_pin_sh, HIGH);
		digitalWrite(_pin_sh, LOW);
	}
}

void Sig16::display() const
{
	digitalWrite(_pin_st, LOW);
	digitalWrite(_pin_st, HIGH);
}
