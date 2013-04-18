/*
 * VFDTube.h
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#ifndef TUBE_TRAIN_H_
#define TUBE_TRAIN_H_

#include "Arduino.h"
#include "drv_74hc595.h"

#include "tube.h"
#include "iv22.h"

class TubeTrain {
public:
	TubeTrain(uint8_t pin_din, uint8_t pin_sh, uint8_t pin_st, uint8_t pin_oe, byte count);
	virtual ~TubeTrain();
	void display();
	void initTube(byte index, Tube * tube);

	Tube& getTube(byte index);
	void printf(const char *__fmt, ...);

private:
	Drv74hc595 _chip;
	const byte _count;
	Tube ** _train;

};

#endif /* TUBE_TRAIN_H_ */
