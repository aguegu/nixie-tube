/*
 * NixieTube.cpp
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

