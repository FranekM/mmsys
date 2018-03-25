#include <stdio.h>
#include "utf8.h"

int getmap[4] = {/*0x3F, 0x7F, */0x3F, 0x1F, 0x0F, 0x07};
int putmap[4] = {/*0x00, 0x00, */0x00, 0x06, 0x0B, 0x0F};

int join(int, int, int);
int sqByte(int);

int getcp(FILE *file) {
	
	int c = fgetc(file);
	
	if (c < 0x08)
		return c;
	if ((c & 0x0C) == 0x80)
		return c & 0x3F;
	
	int rqNext = sqByte(c);
	int codePoint = join(0, c, rqNext);
	
	while (rqNext-- > 0) {
		c = fgetc(file);
		codePoint = join(codePoint, c, 0);
	}
	
	return codePoint;
	
//	int c = fgetc(file);
//	int rqNext = sqByte(c);
//	int codePoint = 0;
//	pasteInto(&codePoint, c, rqNext+1);
//	
//	while (rqNext > 0) {
//		c = fgetc(file);
//		pasteInto(&codePoint, c, 2);
//		rqNext--;
//	}
	
//	do {
//		c = fgetc(file);
//		if (c == EOF)
//			return EOF;
//		insq += sqByte(c);
//		pasteInto(&codePoint, c, insq+1);
//	} while (insq > 0);
	
	return codePoint;
}

int join(int value, int c, int pos) {
//	printf("%X - ", c);
//	printf("%X - ", c & getmap[pos]);
//	printf("%X - ", (c & getmap[pos]) << putmap[pos]);
//	printf("%X \n", *codePoint | ((c & getmap[pos]) << putmap[pos]));
	return value |= (c & getmap[pos]) << putmap[pos];
}

int sqByte(int c) {
	
//	if (c < 0x80)
//		return 0;
//	if ((c & 0xC0) == 0x80)
//		return -1;
	if ((c & 0xE0) == 0xC0)
		return 1;
	if ((c & 0xF0) == 0xE0)
		return 2;
	if ((c & 0xF8) == 0xF0)
		return 3;
	else
		return 0;
	
}
