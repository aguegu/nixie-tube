/*
 * tube.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: agu
 */

#include "tube.h"

Tube::Tube() {
	_buff = NULL;
}

Tube::~Tube() {

}

byte * Tube::getBuff() {
	return _buff;
}

void Tube::setBuff(byte *p, byte length){
	memcpy(_buff, p, min(getBuffLength(), length));
}
