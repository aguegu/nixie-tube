/*
 * VFDTube.h
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#ifndef VFDTUBE_H_
#define VFDTUBE_H_

#include "Arduino.h"

class VFDTube
{
public:

	VFDTube(uint8_t pin_din, uint8_t pin_oe, uint8_t pin_st, uint8_t pin_sh, byte section_count);
	virtual ~VFDTube();

	void enable(bool on = true);
	void display();

	void putWord(byte index, word value = 0x7000);
	void clear(word value = 0x7000);

private:

	word *_buff;
	char * _cache;

	const uint8_t _pin_din; // DA
	const uint8_t _pin_oe; // OE, PWM strongly recommended
	const uint8_t _pin_st; // STCP
	const uint8_t _pin_sh; // SHCP

	const byte _section_count;
	const byte _cache_length;

	void send(byte data) const;
};

#endif /* VFDTUBE_H_ */
