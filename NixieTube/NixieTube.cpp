/*
 * NixieTube.cpp
 *
 * Library for Nixie (Tube) Module for Arduino,
 * developed by Yan Zeyuan @ http://nixieclock.org
 *
 * Created on: 2012-5-4
 * Author: Weihong Guan (aGuegu) @ http://aguegu.net
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

