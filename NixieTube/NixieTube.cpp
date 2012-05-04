/*
 * NixieTube.cpp
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

#include "NixieTube.h"

NixieTube::NixieTube(uint8_t pin_din, uint8_t pin_st, uint8_t pin_sh, uint8_t pin_oe, byte section_count)
{
	_section_count = section_count;
	_buff = (byte *)malloc(sizeof(byte) * section_count * 2);

	_pin_dt = pin_din;
	_pin_st = pin_st;
	_pin_sh = pin_sh;
	_pin_oe = pin_oe;

	pinMode(_pin_dt, OUTPUT);
	pinMode(_pin_st, OUTPUT);
	pinMode(_pin_sh, OUTPUT);
	pinMode(_pin_oe, OUTPUT);
}

NixieTube::~NixieTube()
{
	free(_buff);
}

