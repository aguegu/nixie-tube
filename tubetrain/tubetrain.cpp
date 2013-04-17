/*
 * VFDTube.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#include "tubetrain.h"

TubeTrain::TubeTrain(uint8_t pin_din, uint8_t pin_sh, uint8_t pin_st,
		uint8_t pin_oe, byte count) :
		_chip(pin_din, pin_sh, pin_st, pin_oe), _count(count) {
	_train = (Tube **) malloc(sizeof(Tube*) * _count);

	for (byte i = 0; i < _count; i++)
		_train[i] = NULL;

	_chip.setOE(LOW);
}

TubeTrain::~TubeTrain() {
	free(_train);
}

void TubeTrain::initTube(byte index, Tube *tube) {
	if (index >= _count)
		return;
	_train[index] = tube;
}

void TubeTrain::display() {

	for (byte i = 0; i < _count; i++) {
		_train[i]->runEffect();
		_chip.shiftSend(_train[i]->getBuff(), _train[i]->getBuffLength());
	}
	_chip.shiftLatch();
}

Tube& TubeTrain::getTube(byte index) {
	return *(_train[index]);
}

