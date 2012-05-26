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
 * Instruction:
 *
 * i. 	Only 4 pins are needed to control the module, just like all we need for 74HC595
 * ii. 	_pin_oe has to be connected to a PWM pin to enable brightness control.
 * 		set brightness ranges from 0 to 255. Setting 0 to turn off the module.
 * 		set beughtness at a low level, like 0x20,
 * 		would save lots of power and extend the lifetime of the tube.
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
	// set section_count to how many the sections plugged in the chain, default value is 1

	virtual ~NixieTube();

	void clear(word value = 0x7000);

	void putWord(byte index, word value = 0x7000);
	// Test function

	void setBrightness(byte brightness = 0x40);
	void display();

	void setBackgroundColor(Color color);
	void setBackgroundColor(byte index, Color color);

	void setNumber(byte num);
	void setNumber(byte index, byte num);

	void setColon(byte index, Colon colon);
	void setColon(Colon colon);

	void printf(const char *__fmt, ...);


private:

	word *_buff;
	char * _cache;

	const uint8_t _pin_dt; // DIN, #1
	const uint8_t _pin_st; // STCP, #2
	const uint8_t _pin_sh; // SHCP, #3
	const uint8_t _pin_oe; // OE,	 #4, PWM strongly recommended
	const byte _section_count;

	byte _cache_length;

	void send(byte data) const;
	bool isNumber(char c);
	bool isColon(char);
	void putCache();

	Colon getColon(char c);
};

#endif /* NIXIETUBE_H_ */
