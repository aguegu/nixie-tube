/*
 * Iv17Test.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: agu
 */

/*
#define TUBE_COUNT 1

uint8_t _pin_din = 4;
uint8_t _pin_clk = 7;
uint8_t _pin_load = ;
uint8_t _pin_blank = 7;

uint8_t pattern[] =
		{ 0xbb, 0x12, 0xae, 0xb6, 0x17, 0xb5, 0xbd, 0x92, 0xbf, 0xb7 };

uint8_t digit[] = { 15, 14, 13, 16, 12, 17, 11, 18 };

void shift(uint32_t c) {
	for (byte i = 0; i < 20; i++) {
		digitalWrite(_pin_din, bitRead(c,0));
		digitalWrite(_pin_clk, HIGH);
		digitalWrite(_pin_clk, LOW);
		c >>= 1;
	}
	digitalWrite(_pin_load, HIGH);
	digitalWrite(_pin_load, LOW);
}

void setup() {
	pinMode(_pin_din, OUTPUT);
	pinMode(_pin_clk, OUTPUT);
	pinMode(_pin_load, OUTPUT);
	pinMode(_pin_blank, OUTPUT);

	digitalWrite(_pin_blank, LOW);
	digitalWrite(_pin_clk, LOW);
	digitalWrite(_pin_load, LOW);
}

void test(byte k) {
	for (byte i = 0; i < 20; i++) {
		digitalWrite(_pin_din, k != i);
		digitalWrite(_pin_clk, HIGH);
		digitalWrite(_pin_clk, LOW);
	}
	digitalWrite(_pin_load, HIGH);
	digitalWrite(_pin_load, LOW);
}

void loop() {

	for (byte i = 0; i < 8; i++) {
		shift(0x01UL << digit[i] | pattern[i] << 3);
		delay(0x02);
	}
//	static byte i = 3;
//	test(i++);
//	delay(1000);
//
//	if (i >= 20) {
//		i = 3;
//		delay(2000);
//	}
}


*/
