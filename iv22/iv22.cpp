/*
 * Iv22.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: agu
 */

#include "iv22.h"

static const byte PROGMEM IV22_FONT[] = {
		// 0-9
		0xb7, 0x22, 0x9b, 0xab, 0x2e, 0xad, 0xbd, 0x23, 0xbf, 0xaf,

		// a-z
		0xbb, 0xbc, 0x98, 0xba, 0x9f, 0x1d, 0xb5, 0x3c, 0x14, 0xa2, 0x9c, 0x94,
		0x37, 0x38, 0xb8, 0x1f, 0x2f, 0x18, 0x2c, 0x1c, 0xb0, 0x90, 0x0e, 0x0f,
		0x2a, 0x1a, };

Iv22::Iv22() {
	_buff = (byte *) malloc(sizeof(byte) * _BUFF_LENGTH);
	_buff[0] = 0x07;
	_buff[1] = 0x00;
	_frame = 0;
	_pattern_from = 0xa4;
	_pattern_to = 0x00;

	_effect = &Iv22::effectStroke;
	_effect_enable = true;
}

Iv22::~Iv22() {
	free(_buff);
}

void Iv22::setEffectEnable(bool en) {
	_effect_enable = en;
}

void Iv22::setValue(word value) {
	setBuff((byte[] ) { highByte(value), lowByte(value) }, _BUFF_LENGTH);
}

void Iv22::setPoint(byte on) {
	bitWrite(_buff[1], 6, on);
}

void Iv22::setPatternCurrent(byte pattern) {
	_buff[1] &= 0x40;
	_buff[1] |= pattern;
}

void Iv22::setPatternDest(byte pattern) {
	_pattern_to &= 0x40;
	_pattern_to |= pattern;
}

byte Iv22::getPatternCurrent(void) {
	return _buff[1] & 0xbf;
}

void Iv22::setChar(char c) {

	byte index = convertCharToIndex(c);

	if (index == 255)
		return;

	_effect_enable ?
			this->setPatternDest(pgm_read_byte_near(IV22_FONT + index)) :
			this->setPatternCurrent(pgm_read_byte_near(IV22_FONT + index));
}

byte Iv22::convertCharToIndex(char c) {
	byte index = 255;
	if (c >= '0' && c <= '9')
		index = c - '0';
	else if (c >= 'A' && c <= 'Z')
		index = c - 'A' + 10;
	else if (c >= 'a' && c <= 'z')
		index = c - 'a' + 10;
	return index;
}

void Iv22::runEffect() {

	if (_pattern_from == _pattern_to)
		return;

// finish effect in 16 units
	if (_frame < 16) {
		(this->*_effect)();
		_frame++;
	} else {
		_pattern_from = _pattern_to;
		_frame = 0;
		this->setPatternCurrent(_pattern_to);
	}
}

void Iv22::effectBlink() {
	this->setPatternCurrent(_frame & 0x02 ? _pattern_to : _pattern_from);
}

static const byte PROGMEM ROLL_MASK[4] = { 0xbe, 0xb8, 0xb0, 0x80 };
void Iv22::effectRoll() {

	this->setPatternCurrent(
			_frame < 8 ?
					_pattern_from
							& pgm_read_byte_near(ROLL_MASK + (_frame >> 1)) :
					_pattern_to
							& pgm_read_byte_near(ROLL_MASK + 7 - (_frame >> 1)));
}

static const byte PROGMEM SLIP_MASK[4] = { 0xab, 0xab, 0x22, 0x00 };
void Iv22::effectSlip() {

	this->setPatternCurrent(
			_frame < 8 ?
					_pattern_from
							& pgm_read_byte_near(SLIP_MASK + (_frame >> 1)) :
					_pattern_to
							& pgm_read_byte_near(SLIP_MASK + 7 - (_frame >> 1)));
}

static const uint8_t PROGMEM STROCK_ORDER[] = { 2, 4, 7, 5, 1, 8, 0, // 0
		1, 8, 8, 5, 8, 8, 8, // 1
		7, 4, 8, 3, 8, 1, 0, // 2
		0, 1, 3, 8, 8, 5, 7, // 3
		5, 1, 8, 8, 3, 8, 2, // 4
		0, 2, 8, 8, 3, 5, 7, // 5
		0, 2, 8, 4, 7, 5, 3, // 6
		0, 8, 8, 1, 8, 8, 5, // 7
		1, 0, 2, 4, 7, 5, 3, // 8
		3, 8, 2, 0, 1, 5, 7, // 9
		};

void Iv22::effectStroke() {
	if (_frame < 7) {
		byte index = this->getPatternIndex(_pattern_from);
		if (index > 9)
			return;
		byte c = pgm_read_byte_near(STROCK_ORDER + 7 * index + 6 - _frame);
		byte tmp = this->getPatternCurrent();
		bitClear(tmp, c);
		this->setPatternCurrent(tmp);
	} else if (_frame > 8) {
		byte index = this->getPatternIndex(_pattern_to);
		if (index > 9)
			return;
		byte c = pgm_read_byte_near(STROCK_ORDER + 7 * index + _frame - 9);
		byte tmp = this->getPatternCurrent();
		bitSet(tmp, c);
		this->setPatternCurrent(tmp);
	}
}

byte Iv22::getPatternIndex(byte pattern) {
	byte i;
	for (i = 0; i < 10 && pattern != pgm_read_byte_near(IV22_FONT + i); i++)
		;
	return i;
}

byte Iv22::getBuffLength() {
	return _BUFF_LENGTH;
}

static const uint8_t PROGMEM COLORS[] = { 0x07, 0x06, 0x05, 0x04, 0x03, 0x02,
		0x01, 0x00 };

void Iv22::setColor(Tube::Color color) {
	_buff[0] = pgm_read_byte_near(COLORS + color);
}
