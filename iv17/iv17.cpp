/*
 * Iv17.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: agu
 */

#include "iv17.h"

/*
 * 		--- ---			6		c
 * 		|\ | /|		5	8	9	a	d
 * 		| \|/ |
 * 		--- ---			7		b
 * 		| /|\ |
 * 		|/ | \|		4	2	1	0	e
 * 		--- ---		  	3		f
 *
 */

Iv17::Iv17() {
	_buff = (byte *) malloc(sizeof(byte) * _BUFF_LENGTH);
	_buff[0] = 0x00;
	_buff[1] = 0x00;
	_buff[2] = 0xe8;
	// 0x08: blue led
	// 0x10: red led -
	// 0x20: green led -
	// 0x40: right dot -
	// 0x80: left dot -
}

Iv17::~Iv17() {
	free(_buff);
}

byte Iv17::getBuffLength() {
	return _BUFF_LENGTH;
}
