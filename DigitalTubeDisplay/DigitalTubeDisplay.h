/*
 * DigitalTubeDisplay.h
 *
 *  Created on: 2012-2-12
 *      Author: Agu
 *
 *         a
 *       -----
 *    f |     | b
 *      |  g  |
 *       -----
 *    e |     | c
 *      |     |
 *       -----  . cp
 *         d
 *
 */


#ifndef DIGITAL_TUBE_DISPLAY_H_
#define DIGITAL_TUBE_DISPLAY_H_

#include "Arduino.h"
#include "DigitalTubeFont.h"


class DigitalTubeDisplay
{
public:
	//DigitalTubeDisplay(uint8_t pin_DIG1, uint8_t pin_DIG2, uint8_t pin_DIG3, uint8_t pin_DIG4, uint8_t pin_A, uint8_t pin_B, uint8_t pin_C, uint8_t pin_D, uint8_t pin_E, uint8_t pin_F, uint8_t pin_G, uint8_t pin_DP);
	//DigitalTubeDisplay dtd(9, 10, 11, 8, 0, 2, 6, 4, 3, 1, 7, 5);
	DigitalTubeDisplay(uint8_t pin_DIG1 = 2, uint8_t pin_DIG2 = 11, uint8_t pin_DIG3 = 12, uint8_t pin_DIG4 = 9, uint8_t pin_A = 3, uint8_t pin_B = 13, uint8_t pin_C = 10, uint8_t pin_D = 6, uint8_t pin_E = 5, uint8_t pin_F = 4, uint8_t pin_G = 8, uint8_t pin_DP = 7);
	virtual ~DigitalTubeDisplay();

	void turnOff();
	void turnOn();

	void setDelaySpan(uint16_t span);

	void setPointAt(byte posi);
	void clear(byte val = 0x00);
	void display(word times = 1);
	void setPattern(byte index, byte pattern);

	void printf(const char *__fmt, ...);

private:
	uint8_t _pin_E[4];
	uint8_t _pin_D[8];
	uint16_t _delaySpan;
	byte * _cache;
	void putPattern(byte pattern);
};

#endif /* DIGITALTUBEDISPLAY_H_ */
