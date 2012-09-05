/*
 * DigitalTubeDisplay.cpp
 *
 *  Created on: 2012-2-12
 *      Author: Agu
 */

#include "DigitalTubeDisplay.h"

DigitalTubeDisplay::DigitalTubeDisplay(uint8_t pin_DIG1, uint8_t pin_DIG2,
		uint8_t pin_DIG3, uint8_t pin_DIG4, uint8_t pin_A, uint8_t pin_B,
		uint8_t pin_C, uint8_t pin_D, uint8_t pin_E, uint8_t pin_F,
		uint8_t pin_G, uint8_t pin_DP)
{
	_delaySpan = 0x1000;

	_pin_E[0] = pin_DIG1;
	_pin_E[1] = pin_DIG2;
	_pin_E[2] = pin_DIG3;
	_pin_E[3] = pin_DIG4;

	_pin_D[0] = pin_A;
	_pin_D[1] = pin_B;
	_pin_D[2] = pin_C;
	_pin_D[3] = pin_D;
	_pin_D[4] = pin_E;
	_pin_D[5] = pin_F;
	_pin_D[6] = pin_G;
	_pin_D[7] = pin_DP;

	for (byte i = 0; i < 4; i++)
		pinMode(_pin_E[i], OUTPUT);

	for (byte i = 0; i < 8; i++)
		pinMode(_pin_D[i], OUTPUT);

	this->turnOff();

	_cache = (byte*) malloc(sizeof(byte) * 4);
}

void DigitalTubeDisplay::turnOff()
{
	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_E[i], LOW);
}

void DigitalTubeDisplay::turnOn()
{
	for (byte i = 0; i < 8; i++)
		digitalWrite(_pin_D[i], LOW);

	for (byte i = 0; i < 4; i++)
		digitalWrite(_pin_E[i], HIGH);
}

DigitalTubeDisplay::~DigitalTubeDisplay()
{
	free(_cache);
}

void DigitalTubeDisplay::putPattern(byte pattern)
{
	for (byte i = 0; i < 8; i++)
	{
		digitalWrite(_pin_D[i], bit_is_clear(pattern, i));
	}
}

void DigitalTubeDisplay::setDelaySpan(uint16_t span)
{
	_delaySpan = span;
}

void DigitalTubeDisplay::clear(byte val)
{
	memset(_cache, val, 4);
}

void DigitalTubeDisplay::display(word times)
{
	while (times--)
		for (byte i = 0; i < 4; i++)
		{
			this->putPattern(_cache[i]);

			digitalWrite(_pin_E[i], HIGH);
			delayMicroseconds(_delaySpan);
			digitalWrite(_pin_E[i], LOW);
		}
}

void DigitalTubeDisplay::setPattern(byte index, byte pattern)
{
	if (index > 3)
		return;
	_cache[index] = pattern;
}

void DigitalTubeDisplay::printf(const char *__fmt, ...)
{
	char * p = (char*) malloc(sizeof(char) * 5);
	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(p, 9, __fmt, ap);
	va_end(ap);

	this->clear();
	byte index = 0;
	byte ptr = 0;
	while (p[index] && ptr < 4)
	{
		if (p[index] >= '0' && p[index] <= '9')
		{
			_cache[ptr] = pgm_read_byte_near(DIGITAL_TUBE_FONT+p[index] - 0x30);
			ptr++;
		}
		else if (p[index] >= 'A' && p[index] <= 'F')
		{
			_cache[ptr] = pgm_read_byte_near(DIGITAL_TUBE_FONT+p[index] - 55);
			ptr++;
		}
		else if (p[index] >= 'a' && p[index] <= 'f')
		{
			_cache[ptr] = pgm_read_byte_near(DIGITAL_TUBE_FONT+p[index] - 87);
			ptr++;
		}
		else if (p[index] == '.')
			_cache[ptr?ptr-1:0] |= 0x80;
		else
		{
			_cache[ptr] = 0x00;
			ptr++;
		}

		index++;
	}
	free(p);
}
