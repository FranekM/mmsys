#include <stdlib.h>
#include <stdio.h>
#include "utf8.h"

static const int getmap[4] = {0x3F, 0x1F, 0x0F, 0x07};
static const int putmap[4] = {0x00, 0x06, 0x0C, 0x12};
static const int prefix[4] = {0x80, 0xC0, 0xE0, 0xF0};

static int require(int);

void utf8_write(FILE *file, int codePoint) {
	if (codePoint < 0x80) {
		fputc(codePoint, file);
		return;
	}
	
	int bytes = require(codePoint);
	int c = (codePoint >> putmap[bytes]) & getmap[bytes] | prefix[bytes];
	fputc(c, file);
	while (bytes-- > 0) {
		c = (codePoint >> putmap[bytes]) & getmap[0] | prefix[0];
		fputc(c, file);
	}
}

void utf8_writeword(FILE *file, int *word) {
	while (*word != '\0')
		utf8_write(file, *word++);
}

void utf8_writeline(FILE *file, int *line) {
	utf8_writeword(file, line);
	utf8_write(file, '\n');
}

int require(int c) {
	if (c < 0x800)
		return 1;
	if (c < 0x10000)
		return 2;
	if (c < 0x200000)
		return 3;
	return 0;
}
