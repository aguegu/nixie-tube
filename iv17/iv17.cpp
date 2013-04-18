/*
 * Iv17.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: agu
 */

#include "iv17.h"

Iv17::Iv17() {
	_buff = (byte *) malloc(sizeof(byte) * _BUFF_LENGTH);
	_buff[0] = 0x30;
	_buff[1] = 0x00;
	_buff[2] = 0x00;
}

Iv17::~Iv17() {
	free(_buff);
}

byte Iv17::getBuffLength() {
	return _BUFF_LENGTH;
}
