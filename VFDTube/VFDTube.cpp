/*
 * VFDTube.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#include "VFDTube.h"

VFDTube::VFDTube(uint8_t pin_din, uint8_t pin_oe, uint8_t pin_st,
		uint8_t pin_sh, byte section_count) :
		_pin_din(pin_din), _pin_oe(pin_oe), _pin_st(pin_st), _pin_sh(pin_sh), _section_count(
				section_count), _cache_length(section_count * 2 + 1)
{
	_buff = (word *) malloc(sizeof(word) * section_count);
	_cache = (char *) malloc(sizeof(char) * _cache_length);

	pinMode(_pin_din, OUTPUT);
	pinMode(_pin_st, OUTPUT);
	pinMode(_pin_sh, OUTPUT);
	pinMode(_pin_oe, OUTPUT);

	this->enable();

	memset(_cache, 0, _cache_length);
}

VFDTube::~VFDTube()
{
	free(_buff);
	free(_cache);
}

void VFDTube::enable(bool on)
{
	digitalWrite(_pin_oe, !on);
}

void VFDTube::send(byte data) const
{
	for (byte i = 8; i > 0; i--)
	{
		digitalWrite(_pin_din, bitRead(data, i - 1));
		digitalWrite(_pin_sh, LOW);
		digitalWrite(_pin_sh, HIGH);
	}

	digitalWrite(_pin_st, LOW);
	digitalWrite(_pin_st, HIGH);
}

void VFDTube::display()
{
	for (byte i = 0; i < _section_count; i++)
	{
		this->send(highByte(_buff[i]));
		this->send(lowByte(_buff[i]));
	}

	digitalWrite(_pin_st, LOW);
	digitalWrite(_pin_st, HIGH);
}

void VFDTube::putWord(byte index, word value)
{
	index %= _section_count;
	_buff[index] = value;
}

void VFDTube::clear(word value)
{
	for (byte i = 0; i < _section_count; i++)
		this->putWord(i, value);
}
