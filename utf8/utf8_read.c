#include <stdlib.h>
#include <stdio.h>
#include "utf8.h"

#define MAXBUF 1000

static const int getmap[4] = {0x3F, 0x1F, 0x0F, 0x07};
static const int putmap[4] = {0x00, 0x06, 0x0C, 0x12};
static int buffer[MAXBUF];

static int require(int);
static int skipBOM(FILE *);
static int with_space(int);
static int with_newline(int);

int utf8_read(FILE *file) {
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

int *utf8_bufread(FILE *file, int (*end)(int)) {
	int c, i = skipBOM(file);
	if (buffer[0] == EOF)
		return NULL;
	do
		buffer[i++] = c = utf8_read(file);
	while (!end(c) && c != EOF && i < MAXBUF);
	int *word = malloc(i * sizeof(int));
	word[--i] = '\0';
	while (--i >= 0)
		word[i] = buffer[i];
	return word;
}

int *utf8_readword(FILE *file) {
	return utf8_bufread(file, with_space);
}

int *utf8_readline(FILE *file) {
	return utf8_bufread(file, with_newline);
}

int with_space(int code) {
	return isWhitespace(code);
}

int with_newline(int code) {
	return code == '\n';
}

int skipBOM(FILE *file) {
	if ((buffer[0] = utf8_read(file)) == BOM)
		return 0;
	return 1;
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
