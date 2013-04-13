//============================================================================
// Name        : Rebyte.cpp
// Author      : aGuegu
// Version     :
// Copyright   : copyright @ aguegu.net
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>

/* 	 	   0
 * 		 ------
 *		5|	  |
 *		 | 6  |1
 *		 ------
 *		4|    |
 *		 | 3  |2
 *		 ------  -7
 */

static const unsigned char DIGITAL_TUBE_FONT[] = {
	// 0-10
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,

	// a-z
	0x5f, // a
	0x7c, // b
	0x58, // c
	0x5e, // d
	0x7b, // e
	0x71, // f
	0x3d, // G
	0x74, // h
	0x30, // I
	0x0e, // J
	0x78, // k
	0x38, // L
	0x37, // M
	0x54, // n
	0x5c, // O
	0x73, // P
	0x67, // q
	0x50, // r
	0x64, // s
	0x70, // t
	0x1c, // u
	0x18, // v
	0x62, // w
	0x63, // x
	0x46, // y
	0x52, // z
};

std::string bytestr(unsigned char c) {
	char tmp[3];
	sprintf(tmp, "%02x", c);
	std::string ref(tmp);
	return ref;
}

int main() {

	for (unsigned int i = 0; i < sizeof(DIGITAL_TUBE_FONT); i++) {
		unsigned char val = 0x00;
		unsigned char tmp = DIGITAL_TUBE_FONT[i];

		val = tmp & 0x10;

		if (tmp & 0x01)
			val |= 0x02;
		if (tmp & 0x02)
			val |= 0x08;
		if (tmp & 0x04)
			val |= 0x40;
		if (tmp & 0x08)
			val |= 0x80;
		if (tmp & 0x20)
			val |= 0x04;
		if (tmp & 0x40)
			val |= 0x01;
		if (tmp & 0x80)
			val |= 0x20;

		std::cout << "0x" << bytestr(val) << ", " << std::endl;
	}

	exit(EXIT_SUCCESS);
}
