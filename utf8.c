#include <stdio.h>
#include "utf8.h"

int getmap[4] = {0x3F, 0x1F, 0x0F, 0x07};
int putmap[4] = {0x00, 0x06, 0x0C, 0x12};

int require(int);

int getcp(FILE *file) {
	int c = fgetc(file);
	
	if (c < 0x80)
		return c;
	
	int bytes = require(c);
	int codePoint = (c & getmap[bytes]) << putmap[bytes];
	
	while (bytes-- > 0) {
		c = fgetc(file);
		codePoint |= (c & getmap[0]) << putmap[bytes];
	}
	
	return codePoint;
}

int require(int c) {
	if ((c & 0xE0) == 0xC0)
		return 1;
	if ((c & 0xF0) == 0xE0)
		return 2;
	if ((c & 0xF8) == 0xF0)
		return 3;
	return 0;
}
