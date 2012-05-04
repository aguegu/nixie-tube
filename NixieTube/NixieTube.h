/*
 * NixieTube.h
 *
 * Library for Nixie (Tube) Module for Arduino,
 * developed by Yan Zeyuan @ http://nixieclock.org
 *
 * Created on: 2012-5-4
 * Author: Weihong Guan (aGuegu) @ http://aguegu.net
 *
 * Host at https://github.com/aguegu/nixie-tube
 *
 * licensed under Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)
 * http://creativecommons.org/licenses/by-nc/3.0/
 *
 */

#ifndef NIXIETUBE_H_
#define NIXIETUBE_H_

#include "Arduino.h"

class NixieTube
{
public:
	NixieTube(byte section_count);
	virtual ~NixieTube();
private:
	byte *_buff;
	byte _section_count;
	uint8_t _pin_dt;	// DATA, #1
	uint8_t _pin_st;	// STCP, #2
	uint8_t _pin_sh;	// SHCP, #3
	uint8_t _pin_oe;	// OE,	 #4
};

#endif /* NIXIETUBE_H_ */
