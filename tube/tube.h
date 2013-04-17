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

	virtual ~Tube();
	virtual byte * getBuff();
	virtual byte getBuffLength() = 0;
	virtual void transform();
protected:
	Tube();
	byte *_buff;
	virtual bool isDisplayable(char c);
};

#endif /* TUBE_H_ */
