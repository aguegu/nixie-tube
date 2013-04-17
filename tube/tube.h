/*
 * tube.h
 *
 *  Created on: Apr 17, 2013
 *      Author: agu
 */

#ifndef TUBE_H_
#define TUBE_H_

#include "Arduino.h"

class Tube {
public:
	Tube();
	virtual ~Tube();
	virtual byte * getBuff();
	virtual void transform();
protected:
	byte *_buff;
	virtual bool isDisplayable(char c);
};

#endif /* TUBE_H_ */
