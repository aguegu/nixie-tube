/*
 * VFDTube.h
 *
 *  Created on: Oct 29, 2012
 *      Author: agu
 */

#ifndef VFDTUBE_H_
#define VFDTUBE_H_

class VFDTube
{
public:

	VFDTube();
	virtual ~VFDTube();

private:

	word *_buff;
	char * _cache;
	byte _cache_length;

	const uint8_t _pin_dt; // DA
	const uint8_t _pin_st; // STCP
	const uint8_t _pin_sh; // SHCP
	const uint8_t _pin_oe; // OE, PWM strongly recommended
	const byte _section_count;
};

#endif /* VFDTUBE_H_ */
