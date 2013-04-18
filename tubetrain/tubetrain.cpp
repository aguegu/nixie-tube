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

void TubeTrain::printf(const char *__fmt, ...) {

	byte length = _count + 1;
	char *s = (char *) malloc(sizeof(char) * length);

	va_list ap;
	va_start(ap, __fmt);
	vsnprintf(s, length, __fmt, ap);
	va_end(ap);

	for (byte i = 0; i < _count; i++)
		(_train[i])->setChar(s[i]);

	free(s);
}

void TubeTrain::setPoint(byte index, byte point) {
	if (index >= _count)
		return;
	(_train[index])->setPoint(point);
}

void TubeTrain::setColor(byte index, Tube::Color color) {
	if (index >= _count)
		return;
	(_train[index])->setColor(color);
}
