/*
 * DigitalTubeFont.h
 *
 *  Created on: 2012-2-12
 *      Author: Agu
 */

#ifndef DIGITALTUBEFONT_H_
#define DIGITALTUBEFONT_H_

#include <avr/pgmspace.h>

#ifdef PROGMEM
  #undef PROGMEM
  #define PROGMEM __attribute__((section(".progmem.data")))
#endif

extern const uint8_t PROGMEM DIGITAL_TUBE_FONT[] PROGMEM;


#endif /* DIGITALTUBEFONT_H_ */
