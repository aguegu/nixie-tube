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

enum Color
{
	White, Yellow, Cyan, Green,
	Magenta, Red, Blue, Black,
};

enum Colon
{
	None, Upper, Lower, Both
};

class NixieTube
{

public:
	NixieTube(uint8_t pin_din, uint8_t pin_st, uint8_t pin_sh, uint8_t pin_oe,
			byte section_count = 1);
	virtual ~NixieTube();
	void putByte(byte h, byte l);
	void display();
	void setBackgroundColor(Color color);
	void setBackgroundColor(byte index, Color color);

	void setNumber(byte num);
	void setNumber(byte index, byte num);

	void setColon(byte index, Colon colon);
	void putNumber(long value, byte minLength);

private:
	void clear(word value);
	word *_buff;
	byte _section_count;
	uint8_t _pin_dt; // DIN, #1
	uint8_t _pin_st; // STCP, #2
	uint8_t _pin_sh; // SHCP, #3
	uint8_t _pin_oe; // OE,	 #4
};

#endif /* NIXIETUBE_H_ */
