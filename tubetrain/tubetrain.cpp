/*
 * VFDTube.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#include "tubetrain.h"

TubeTrain::TubeTrain(uint8_t pin_din, uint8_t pin_sh, uint8_t pin_st,
		uint8_t pin_oe) :
		_chip(pin_din, pin_sh, pin_st, pin_oe), _train() {
	//_train = new Iv22();
	// new (_train + 0) Iv22();
	_chip.setOE(LOW);
}

TubeTrain::~TubeTrain() {
	//delete _train;
}

void TubeTrain::display(word w) {

//	word x = 0xff;
//	byte c[2];
//	c[0] = highByte(x);
//	c[1] = lowByte(x);

	_train.setValue(w);

	_chip.shiftSend(_train.getBuff(), 2);
	_chip.shiftLatch();

}
