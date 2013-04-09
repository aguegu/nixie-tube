/*
 * Pt6311.cpp
 *
 *  Created on: Dec 13, 2012
 *      Author: agu
 */

#include "pt6311.h"

Pt6311::Pt6311(uint8_t pin_din, uint8_t pin_sck, uint8_t pin_stb) :
		_pin_din(pin_din), _pin_sck(pin_sck), _pin_stb(pin_stb)
{
	_cache = (byte *) malloc(sizeof(byte) * CACHE_LENGTH);
	_str = (char *) malloc(sizeof(char) * (DIGIT_LENGTH + 1));

	pinMode(_pin_din, OUTPUT);
	pinMode(_pin_sck, OUTPUT);
	pinMode(_pin_stb, OUTPUT);

	digitalWrite(_pin_stb, HIGH);
	digitalWrite(_pin_sck, HIGH);
}

Pt6311::~Pt6311()
{
	free(_cache);
	free(_str);
}

void Pt6311::init()
{
	delay(200);

	this->command(0x40);
	this->command(0x00);
	this->setBrightness();

	this->clear();
}

void Pt6311::setBrightness(byte brightness)
{
	if (brightness < 0x08)
		this->command(0x88 + brightness);
	else
		this->command(0x80);
}

void Pt6311::clear(byte val)
{
	memset(_cache, val, CACHE_LENGTH);
}

void Pt6311::setCache(byte index, byte val)
{
	_cache[index % CACHE_LENGTH] = val;
}

void Pt6311::setDigit(byte index, word val)
{
	byte i = (index % DIGIT_LENGTH) * 2;
	_cache[i] = lowByte(val);
	_cache[i + 1] = highByte(val);
}

void Pt6311::setDigitChar(byte index, char chr)
{
	if (chr >= '0' && chr <= '9')
		chr -= '0';
	else if (chr >= 'A' && chr <= 'Z')
		chr -= 'A', chr += 10;
	else if (chr >= 'a' && chr <= 'z')
		chr -= 'a', chr += 10;
	else
		return;

	word pattern = pgm_read_word_near(SIG14_FONT + chr);
	this->setDigit(index, pattern);
}

void Pt6311::transmit(byte cmd)
{
	for (byte i = 0; i < 8; i++)
	{
		digitalWrite(_pin_sck, LOW);
		digitalWrite(_pin_din, bitRead(cmd,i));
		digitalWrite(_pin_sck, HIGH);
	}
}

void Pt6311::command(byte cmd)
{
	digitalWrite(_pin_stb, LOW);
	this->transmit(cmd);
	digitalWrite(_pin_stb, HIGH);
}

void Pt6311::display()
{
	byte * p = _cache + CACHE_LENGTH - 1;

	digitalWrite(_pin_stb, LOW);

	this->transmit(0xc0);

	for (byte i = 0; i < DIGIT_LENGTH; i++)
	{
		this->transmit(*(--p));
		this->transmit(*(++p));
		p--;
		p--;
		this->transmit(0x00);
	}

	digitalWrite(_pin_stb, HIGH);
}

void Pt6311::printf(const char *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(_str, 9, __fmt, ap);
	va_end(ap);

	for (byte i = 0; i < DIGIT_LENGTH; i++)
		this->setDigitChar(i, _str[i]);
}

void Pt6311::putDot(byte index)
{
	switch (index)
	{
	case 0:
		_cache[3] |= 0x20;
		break;
	case 1:
		_cache[3] |= 0x80;
		break;
	case 2:
		_cache[7] |= 0x20;
		break;
	case 3:
		_cache[11] |= 0x20;
		break;
	case 4:
		_cache[11] |= 0x80;
		break;
	}
}
