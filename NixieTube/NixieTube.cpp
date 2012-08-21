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
 * Pin Layout, right-side view, input from pins(male)
 *
 *              /-------------\
 *              |             |
 *              |             |
 *              |             |
 *              \-------------/
 *               |           |
 * -----------------------------
 * | SH  | ST  | DS  |
 * | 5V  | GND | OE  |
 * -------------------
 * | 12V | 12V | 12V |
 * | GND | GND | GND |
 * -----------------------------
 *
 */

#include "NixieTube.h"

NixieTube::NixieTube(uint8_t pin_din, uint8_t pin_st, uint8_t pin_sh,
		uint8_t pin_oe, byte section_count) :
		_pin_dt(pin_din), _pin_st(pin_st), _pin_sh(pin_sh), _pin_oe(pin_oe), _section_count(
				section_count)
{
	_cache_length = section_count * 2 + 1;
	_buff = (word *) malloc(sizeof(word) * section_count);
	_cache = (char *) malloc(sizeof(char) * _cache_length);

	pinMode(_pin_dt, OUTPUT);
	pinMode(_pin_st, OUTPUT);
	pinMode(_pin_sh, OUTPUT);
	pinMode(_pin_oe, OUTPUT);

	this->setBrightness();

	this->clear();

	memset(_cache, 0, _cache_length);

}

void NixieTube::send(byte data) const
{
	for (byte i = 8; i > 0; i--)
	{
		digitalWrite(_pin_dt, bitRead(data, i - 1));
		digitalWrite(_pin_sh, LOW);
		digitalWrite(_pin_sh, HIGH);
	}
}

void NixieTube::display()
{
	for (byte i = 0; i < _section_count; i++)
	{
		this->send(highByte(_buff[i]));
		this->send(lowByte(_buff[i]));
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

void NixieTube::setBrightness(byte brightness)
{
	if (digitalPinToTimer(_pin_oe) == NOT_ON_TIMER)
		digitalWrite(_pin_oe, brightness ? LOW : HIGH);
	else
		analogWrite(_pin_oe, 0xff - brightness);
}

void NixieTube::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_cache, _cache_length, __fmt, ap);
	va_end(ap);

	this->putCache();
}

bool NixieTube::isNumber(char c)
{
	return (c >= '0' && c <= '9');
}

bool NixieTube::isColon(char c)
{
	return (c == ':' || c == '\'' || c == '.');
}

Colon NixieTube::getColon(char c)
{
	Colon cln = None;
	switch (c)
	{
	case ':':
		cln = Both;
		break;
	case '.':
		cln = Lower;
		break;
	case '\'':
		cln = Upper;
		break;
	default:
		cln = None;
		break;
	}

	return cln;
}

void NixieTube::putCache()
{
	char * p = _cache;

	this->setNumber(-1);
	this->setColon(None);

	byte index = 0;
	byte ptr = 0;
	while (p[index] && index < _cache_length)
	{
		if (this->isNumber(p[index]))
		{
			this->setNumber(ptr, p[index] - 0x30);
			ptr++;
		}
		else if (this->isColon(p[index]))
		{

			this->setColon(ptr ? ptr - 1 : 0, getColon(p[index]));
		}
		else
		{
			this->setNumber(ptr, -1);
			ptr++;
		}

		index++;
	}
}

NixieTube::~NixieTube()
{
	free(_buff);
	free(_cache);
}

