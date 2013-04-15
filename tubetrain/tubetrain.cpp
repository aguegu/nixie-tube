/*
 * VFDTube.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#include "tubetrain.h"

TubeTrain::TubeTrain(uint8_t pin_din, uint8_t pin_sh, uint8_t pin_st,
		uint8_t pin_oe) :
		_chip(pin_din, pin_sh, pin_st, pin_oe) {
	_train[0] = new Iv22();
	_chip.setOE(LOW);
}

TubeTrain::~TubeTrain() {
	//delete[] (_train);
}

void TubeTrain::display(word w) {

	_train[0]->setValue(w);

	_chip.shiftSend(_train[0]->getBuff(), 2);
	_chip.shiftLatch();

}
