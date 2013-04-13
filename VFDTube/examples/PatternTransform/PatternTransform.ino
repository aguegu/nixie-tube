#include "VFDTube.h"

#define TUBE_COUNT 1

VFDTube tube(4, 5, 6, 7, TUBE_COUNT);
// DIN on pin #4, OE on pin #5, STCP on pin #6, SHCP on pin #7,
// TUBE_COUNT stands for sections count in serial
// Pin #5 is with PWM output on UNO, so the brightness is adjustable

const uint8_t PROGMEM STROCK_ORDER[] = { 2, 4, 7, 5, 1, 0, 8, // 0
		1, 5, 8, 8, 8, 8, 8, // 1
		0, 1, 3, 4, 7, 8, 8, // 2
		0, 1, 3, 5, 7, 8, 8, // 3
		2, 3, 1, 5, 8, 8, 8, // 4
		2, 3, 5, 7, 0, 8, 8, // 5
		0, 2, 4, 7, 5, 3, 8, // 6
		0, 1, 5, 8, 8, 8, 8, // 7
		1, 0, 2, 4, 7, 5, 3, // 8
		0, 2, 3, 1, 5, 7, 8, // 9
		};

void transformBlink(byte index, byte dest) {
	byte tmp = tube.getPattern(index);
	for (byte j = 0; j < 4; j++) {
		tube.setPattern(index, tmp);
		tube.display(0x20);

		tube.setPattern(index, dest);
		tube.display(0x20);
	}
}

void transformHalf(byte index, byte dest) {
	byte tmp = tube.getPattern(index);

	tube.setPattern(index, tmp & 0x07);
	tube.display(0x60);

	tube.setPattern(index, (tmp & 0x07) | (dest & 0xe8));
	tube.display(0x60);

	tube.setPattern(index, dest & 0xb8);
	tube.display(0x60);
}

void transformOneThird(byte index, byte dest) {
	byte mask[2] = { 0xab, 0x22 };

	for (byte i = 0; i < 2; i++) {
		tube.setPattern(index, tube.getPattern(index) & mask[i]);
		tube.display(0x60);
	}

	tube.setPattern(index, 0x00);
	tube.display(0x60);

	for (byte i = 0; i < 2; i++) {
		tube.setPattern(index, dest & mask[1 - i]);
		tube.display(0x60);
	}
}

void transformAnd(byte index, byte dest) {
	tube.setPattern(index, tube.getPattern(index) & dest);
	tube.display(0xc0);
}

void transformOr(byte index, byte dest) {
	tube.setPattern(index, tube.getPattern(index) | dest);
	tube.display(0xc0);
}

void transformRoll(byte index, byte dest) {
	byte mask[4] = { 0xbe, 0xb8, 0xb0, 0x80 };

	for (byte i = 0; i < 4; i++) {
		tube.setPattern(index, tube.getPattern(index) & mask[i]);
		tube.display(0x40);
	}

	tube.setPattern(index, 0x00);
	tube.display(0x40);

	for (byte i = 0; i < 4; i++) {
		tube.setPattern(index, dest & (~mask[i] & 0xdf));
		tube.display(0x40);
	}
}

void transformTypeDigit(byte index, byte src, byte dest) {
	byte tmp = tube.getPattern(index);

	for (byte i = 0; i < 7; i++) {
		byte c = pgm_read_byte_near(STROCK_ORDER + 7 * src + 6- i);
		if (c < 8)
			bitClear(tmp, c);
		tube.setPattern(index, tmp);
		tube.display(0x40);
	}

	for (byte i = 0; i < 7; i++) {
		byte c = pgm_read_byte_near(STROCK_ORDER + 7 * dest + i);
		if (c < 8)
			bitSet(tmp, c);
		tube.setPattern(index, tmp);
		tube.display(0x40);
	}
}

void (*pTransform[6])(byte, byte)=
{
	transformBlink,
	transformHalf,
	transformAnd,
	transformOr,
	transformRoll,
	transformOneThird,
};

void setup() {
	tube.clear();
}

void loop() {
	tube.setBackgroundColor(Black);
	for (byte i = 0; i < 10; i++) {
		tube.setPattern(0, pgm_read_byte_near(VFDTUBE_FONT+i));
		tube.display(1000);
	}

	for (byte k = 0; k < 6; k++) {
		tube.setBackgroundColor(0, (Color) ((k + 1) % 7));
		for (byte i = 0; i < 10; i++) {
			tube.setPattern(0, pgm_read_byte_near(VFDTUBE_FONT+i));
			tube.display(1000);
			(*pTransform[k])(0, pgm_read_byte_near(VFDTUBE_FONT+(i+1)%10));
		}

		delay(0x80);
	}

	tube.setBackgroundColor(White);
	for (byte i = 0; i < 10; i++) {
		tube.setPattern(0, pgm_read_byte_near(VFDTUBE_FONT+i));
		tube.display(1000);

		transformTypeDigit(0, i, (i + 1) % 10);
	}
}

