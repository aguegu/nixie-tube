#include "NixieTubeTest.h"
#include "VFDTube.h"

#define TUBE_COUNT 1

VFDTube tube(8, 9, 10, 11, TUBE_COUNT);
// DIN on pin #8, OE on pin #9, STCP on pin #10, SHCP on pin #11,
// 6 for sections count in serial
// Pin #9 is with PWM output, so the brightness is adjustable

byte STROCK_ORDER[] =
{
	2, 4, 7, 5, 1, 0, 8,
	1, 5, 8, 8, 8, 8, 8,
	0, 1, 3, 4, 7, 8, 8,
	0, 1, 3, 5, 7, 8, 8,
	2, 3, 1, 5, 8, 8, 8,
	2, 3, 5, 7, 0, 8, 8,
	0, 2, 4, 7, 5, 3, 8,
	0, 1, 5, 8, 8, 8, 8,
	1, 0, 2, 4, 7, 5, 3,
	0, 2, 3, 1, 5, 7, 8
};

void setup()
{
	tube.setBrightness(0xc0); // set brightness, range 0x00 - 0xff
}

void display(byte index, word val, word span)
{
	tube.putWord(index, val);
	tube.display();
	delay(span);
}

void transformBlink(byte index, word src, word dest)
{
	for (byte j = 0; j < 4; j++)
	{
		display(index, src, 0x20);
		display(index, dest, 0x20);
	}
}

void transformRise(byte index, word src, word dest)
{
	word tmp = 0xff00;

	tmp |= src & 0x07;
	display(index, tmp, 0x60);

	tmp |= dest & 0xe8;
	display(index, tmp, 0x60);

	tmp = 0xff00 | (dest & 0xb8);
	display(index, tmp, 0x60);

//	tmp |= bitRead(src, 3) ? 0x01 : 0x00;
//	tmp |= bitRead(src, 4) ? 0x04 : 0x00;
//	tmp |= bitRead(src, 7) ? 0x08 : 0x00;
//	tmp |= bitRead(src, 5) ? 0x02 : 0x00;

//	tube.putWord(index, dest);
//	tube.display();
//	delay(0x80);

//	tmp |= bitRead(dest, 0) ? 0x08 : 0x00;
//	tmp |= bitRead(dest, 1) ? 0x20 : 0x00;
//	tmp |= bitRead(dest, 2) ? 0x10 : 0x00;
//	tmp |= bitRead(dest, 3) ? 0x80 : 0x00;

//	tube.putWord(index, tmp);
//	tube.display();
//	delay(0x80);
}

void transformAnd(byte index, word src, word dest)
{
	word tmp = src & dest;
	display(index, tmp, 0xc0);
}

void transformOr(byte index, word src, word dest)
{
	word tmp = src | dest;
	display(index, tmp, 0xc0);
}

void transformXor(byte index, word src, word dest)
{
	word tmp = src ^ dest;
	tmp |= 0xff00;
	display(index, tmp, 0xc0);
}

void grow(byte index, byte digit)
{
	word tmp = 0xff00;
	tube.putWord(index, tmp);
	tube.display();
	delay(0x40);

	byte * p = STROCK_ORDER + 7 * digit;

	for (byte i = 0; i < 7; i++)
	{
		if (p[i] < 8)
			bitSet(tmp, p[i]);
		display(index, tmp, 0x40);
	}
}

void loop()
{
	static byte i = 0;

	grow(0, i);

	tube.putWord(0, pgm_read_byte_near(VFDTUBE_FONT+i) | 0xff00);
	tube.display();
	delay(1000);

//	transformAnd(0, pgm_read_byte_near(VFDTUBE_FONT+i) | 0xff00,
//			pgm_read_byte_near(VFDTUBE_FONT+(i+1)%10) | 0xff00);

	i++;

	if (i == 10)
		i = 0;
}

