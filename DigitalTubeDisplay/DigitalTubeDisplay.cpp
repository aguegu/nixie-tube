/*
 * DigitalTubeDisplay.cpp
 *
 *  Created on: 2012-2-12
 *      Author: Agu
 */

#include "DigitalTubeDisplay.h"

DigitalTubeDisplay::DigitalTubeDisplay(uint8_t * pin_digit,
		uint8_t digit_length, uint8_t pin_A, uint8_t pin_B, uint8_t pin_C,
		uint8_t pin_D, uint8_t pin_E, uint8_t pin_F, uint8_t pin_G,
		uint8_t pin_DP) :
		_digit_length(digit_length), _pin_digit(pin_digit)
{
	_pin_segment[0] = pin_A;
	_pin_segment[1] = pin_B;
	_pin_segment[2] = pin_C;
	_pin_segment[3] = pin_D;
	_pin_segment[4] = pin_E;
	_pin_segment[5] = pin_F;
	_pin_segment[6] = pin_G;
	_pin_segment[7] = pin_DP;

	for (byte i = 0; i < _digit_length; i++)
		pinMode(_pin_digit[i], OUTPUT);

	for (byte i = 0; i < 8; i++)
		pinMode(_pin_segment[i], OUTPUT);

	this->turnOff();

	this->setDelaySpan();

	_cache = (byte*) malloc(sizeof(byte) * _digit_length);
}

void DigitalTubeDisplay::turnOff()
{
	for (byte i = 0; i < _digit_length; i++)
		digitalWrite(_pin_digit[i], LOW);
}

void DigitalTubeDisplay::turnOn()
{
	for (byte i = 0; i < 8; i++)
		digitalWrite(_pin_segment[i], LOW);

	for (byte i = 0; i < _digit_length; i++)
		digitalWrite(_pin_digit[i], HIGH);
}

DigitalTubeDisplay::~DigitalTubeDisplay()
{
	free(_cache);
}

void DigitalTubeDisplay::putPattern(byte pattern)
{
	for (byte i = 0; i < 8; i++)
	{
		digitalWrite(_pin_segment[i], bit_is_clear(pattern, i));
	}
}

void DigitalTubeDisplay::setDelaySpan(uint16_t span)
{
	_delaySpan = span;
}

void DigitalTubeDisplay::clear(byte val)
{
	memset(_cache, val, _digit_length);
}

void DigitalTubeDisplay::display(word times)
{
	while (times--)
		for (byte i = 0; i < _digit_length; i++)
		{
			this->putPattern(_cache[i]);

			digitalWrite(_pin_digit[i], HIGH);
			delayMicroseconds(_delaySpan);
			digitalWrite(_pin_digit[i], LOW);
		}
}

void DigitalTubeDisplay::setPattern(byte index, byte pattern)
{
	if (index >= _digit_length)
		return;
	_cache[index] = pattern;
}

void DigitalTubeDisplay::printf(const char *__fmt, ...)
{
	char * p = (char*) malloc(sizeof(char) * (_digit_length + 1));
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(p, 9, __fmt, ap);
	va_end(ap);

	this->clear();
	byte index = 0;
	byte ptr = 0;
	while (p[index] && ptr < _digit_length)
	{
		if (p[index] >= '0' && p[index] <= '9')
		{
			_cache[ptr] = pgm_read_byte_near(
					DIGITAL_TUBE_FONT + p[index] - 0x30);
			ptr++;
		}
		else if (p[index] >= 'A' && p[index] <= 'Z')
		{
			_cache[ptr] = pgm_read_byte_near(DIGITAL_TUBE_FONT + p[index] - 55);
			ptr++;
		}
		else if (p[index] >= 'a' && p[index] <= 'z')
		{
			_cache[ptr] = pgm_read_byte_near(DIGITAL_TUBE_FONT + p[index] - 87);
			ptr++;
		}
		else if (p[index] == '.')
			_cache[ptr ? ptr - 1 : 0] |= 0x80;
		else
		{
			_cache[ptr] = 0x00;
			ptr++;
		}

		index++;
	}
	free(p);
}
