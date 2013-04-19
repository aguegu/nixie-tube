/*
 * Iv17.h
 *
 *  Created on: Apr 18, 2013
 *      Author: agu
 */

#ifndef IV17_H_
#define IV17_H_

#include "tube.h"

class Iv17: public Tube {
public:
	Iv17();
	virtual ~Iv17();

	byte getBuffLength();
	void runEffect() {
	}
	;
	void setChar(char c);
	void setPoint(byte c);
	void setColor(Tube::Color color);
private:
	static const byte _BUFF_LENGTH = 3;

	byte convertCharToIndex(char c);
};

#endif /* IV17_H_ */
