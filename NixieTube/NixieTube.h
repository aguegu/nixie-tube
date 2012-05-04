/*
 * NixieTube.h
 * Created on: 2012-5-4
 *
 * Library for Nixie (Tube) Module for Arduino
 * Host: https://github.com/aguegu/nixie-tube
 *
 * licensed under Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)
 * http://creativecommons.org/licenses/by-nc/3.0/
 *
 * Hardware Designer: Yan Zeyuan
 * Blog: http://nixieclock.org
 * Email: yanzeyuan@163.com
 *
 * Library Author: Weihong Guan (aGuegu)
 * Blog: http://aguegu.net
 * Email: weihong.guan@gmail.com
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
