/*
 * NixieTube.cpp
 * Created on: 2012-5-4
 *
 * Library for Nixie (Tube) Module for Arduino
 * Host: https://github.com/aguegu/nixie-tube
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
 */

#include "NixieTube.h"

NixieTube::NixieTube(uint8_t pin_din, uint8_t pin_st, uint8_t pin_sh,
		uint8_t pin_oe, byte section_count):
		_pin_dt(pin_din), _pin_st(pin_st), _pin_sh(pin_sh), _pin_oe(pin_oe),_section_count( section_count)
{

	_buff = (word *) malloc(sizeof(word) * section_count);

	pinMode(_pin_dt, OUTPUT);
	pinMode(_pin_st, OUTPUT);
	pinMode(_pin_sh, OUTPUT);
	pinMode(_pin_oe, OUTPUT);

	this->setBrightness(0x40);

	this->clear();

}

void NixieTube::send(byte data) const
{
	for (byte i = 8; i > 0; i--)
	{
		digitalWrite(_pin_dt, bitRead(data, i-1));
		digitalWrite(_pin_sh, LOW);
		digitalWrite(_pin_sh, HIGH);
	}
}

void NixieTube::display()
{
	for (byte i = _section_count; i > 0; i--)
	{
		this->send(highByte(_buff[i-1]));
		this->send(lowByte(_buff[i-1]));
	}

	digitalWrite(_pin_st, LOW);
	digitalWrite(_pin_st, HIGH);
}

void NixieTube::putWord(byte index, word value)
{
	index %= _section_count;
	_buff[index] = value;
}

void NixieTube::clear(word value)
{
	for (byte i = 0; i < _section_count; i++)
		this->putWord(i, value);
}

void NixieTube::setBackgroundColor(Color color)
{
	for (byte i = 0; i < _section_count; i++)
	{
		this->setBackgroundColor(i, color);
	}
}

void NixieTube::setBackgroundColor(byte index, Color color)
{
	index %= _section_count;
	_buff[index] &= 0x8fff;
	_buff[index] |= color << 12;
}

void NixieTube::setNumber(byte index, byte num)
{
	_buff[index] &= 0xfc00;

	if (num == 0xff)
		return;

	num = (num + 9) % 10;
	_buff[index] |= _BV(num);
}

void NixieTube::setNumber(byte num)
{
	for (byte i = 0; i < _section_count; i++)
		this->setNumber(i, num);
}

void NixieTube::setColon(byte index, Colon colon)
{
	_buff[index] &= 0xf3ff;
	_buff[index] |= colon << 10;
}

void NixieTube::setColon(Colon colon)
{
	for (byte i = 0; i < _section_count; i++)
		this->setColon(i, colon);
}

void NixieTube::putNumber(unsigned long value, byte index, byte minLength)
{
	for (byte i = index; i < _section_count; i++)
	{
		byte num = value % 10;
		this->setNumber(i, num);
		if (value == 0 && i >= index + minLength)
			this->setNumber(i, -1);
		value /= 10;
	}
}

void NixieTube::setBrightness(byte brightness)
{
	if (digitalPinToTimer(_pin_oe) == NOT_ON_TIMER)
		digitalWrite(_pin_oe, brightness ? LOW : HIGH);
	else
		analogWrite(_pin_oe, 0xff - brightness);
}

NixieTube::~NixieTube()
{
	free(_buff);
}

