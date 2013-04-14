/*
 * Iv22.cpp
 *
 *  Created on: Apr 15, 2013
 *      Author: agu
 */

#include "iv22.h"

Iv22::Iv22() {
	_buff = (byte *) malloc(sizeof(byte) * _BYTE_PER_SECTION);

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

byte Iv22::getPattern(void) {
	return _buff[1] & 0xbf;
}

bool Iv22::setChar(char c) {

	bool val = isDisplayable(c);

	if (val) {
		if (c >= '0' && c <= '9')
			this->setPattern(pgm_read_byte_near(VFDTUBE_FONT + c - '0'));
		else if (c >= 'A' && c <= 'Z')
			this->setPattern(pgm_read_byte_near(VFDTUBE_FONT + c - 'A' + 10));
		else if (c >= 'a' && c <= 'z')
			this->setPattern(pgm_read_byte_near(VFDTUBE_FONT + c - 'a' + 10));
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
