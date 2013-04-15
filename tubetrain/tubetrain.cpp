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
	_train = (Iv22 **) malloc(sizeof(Iv22*) * _count);

	for (byte i = 0; i < _count; i++)
		_train[i] = new Iv22();

	_chip.setOE(LOW);

}

TubeTrain::~TubeTrain() {
	free(_train);
}

void TubeTrain::display() {

	for (byte i = 0; i < _count; i++) {
		_chip.shiftSend(_train[i]->getBuff(), 2);
	}
	_chip.shiftLatch();
}

void TubeTrain::callAnimation() {
	for (byte i = 0; i < _count; i++) {
		_train[i]->transform();
	}
}

Iv22& TubeTrain::getTube(byte index) {
	return *_train[index];
}
