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
protected:
	byte *_buff;
};

#endif /* TUBE_H_ */
