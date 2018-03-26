#include <stdio.h>

#define BOM 0xFEFF

int utf8_read(FILE *);
int *utf8_readline(FILE *);
int *utf8_readword(FILE *);

int isWhitespace(int code);
int isPunctation(int code);
