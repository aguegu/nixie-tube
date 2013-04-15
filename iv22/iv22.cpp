/*
 * Iv22.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: agu
 */

#include "iv22.h"

Iv22::Iv22() {
	_buff = (byte *) malloc(sizeof(byte) * _BYTE_PER_SECTION);
	_buff[0] = 0x07;
	_buff[1] = 0x00;
	_frame = 0;
	_pattern_from = 0xa4;
	_pattern_to = 0x00;

	_transform_effect = &Iv22::transformBlink;
}

Iv22::~Iv22() {
	free(_buff);
}

void Iv22::setValue(word value) {
	_buff[0] = highByte(value);
	_buff[1] = lowByte(value);
}

void Iv22::setBackgroundColor(Color color) {
	_buff[0] = color;
}

void Iv22::setPoint(bool on) {
	bitWrite(_buff[1], 6, on);
}

void Iv22::setPattern(byte pattern) {
	_buff[1] &= 0x40;
	_buff[1] |= pattern;
}

void Iv22::setPatternTo(byte pattern) {
	_pattern_to &= 0x40;
	_pattern_to |= pattern;
}

byte Iv22::getPattern(void) {
	return _buff[1] & 0xbf;
}

bool Iv22::setChar(char c) {

	bool val = isDisplayable(c);

	if (val) {
		if (c >= '0' && c <= '9')
			this->setPatternTo(pgm_read_byte_near(VFDTUBE_FONT + c - '0'));
		else if (c >= 'A' && c <= 'Z')
			this->setPatternTo(pgm_read_byte_near(VFDTUBE_FONT + c - 'A' + 10));
		else if (c >= 'a' && c <= 'z')
			this->setPatternTo(pgm_read_byte_near(VFDTUBE_FONT + c - 'a' + 10));
	}

	return val;
}

bool Iv22::isDisplayable(char c) {
	return ((c >= '0' && c <= '9') or (c >= 'A' && c <= 'Z')
			or (c >= 'a' && c <= 'z'));
}

byte * Iv22::getBuff() {
	return _buff;
}

void Iv22::transform() {



	if (_pattern_from == _pattern_to)
		return;

	if (_frame == 0) {
		_pattern_from = this->getPattern();
		_frame++;
	} else if (_frame >= 16) {
		_pattern_from = _pattern_to;
		_frame = 0;
		this->setPattern(_pattern_to);
	} else {
		(this->*_transform_effect)();
		_frame++;
	}
}

void Iv22::transformBlink() {
	this->setPattern(_frame & 0x02 ? _pattern_to : _pattern_from);
}

void Iv22::transformRoll() {
	static const byte mask[4] = { 0xbe, 0xb8, 0xb0, 0x80 };
	this->setPattern(
			_frame < 8 ?
					_pattern_from & mask[_frame >> 1] :
					_pattern_to & mask[7 - (_frame >> 1)]);
}
