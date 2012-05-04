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

NixieTube::NixieTube(byte section_count)
{
	_section_count = section_count;
	_buff = malloc(sizeof(byte) * section_count * 2);

}

NixieTube::~NixieTube()
{
	free(_buff);
}

