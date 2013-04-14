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
#include "iv22.h"

class TubeTrain {
public:
	TubeTrain(uint8_t pin_din, uint8_t pin_sh, uint8_t pin_st, uint8_t pin_oe);
	virtual ~TubeTrain();
	void display(word);
private:
	Drv74hc595 _chip;
	Iv22 _train;
};

#endif /* TUBE_TRAIN_H_ */
