#include <stdio.h>

#define BOM 0xFEFF

int utf8_read(FILE *);
int *utf8_readline(FILE *);
int *utf8_readword(FILE *);

void utf8_write(FILE *, int);
void utf8_writeline(FILE *, int *);
void utf8_writeword(FILE *, int *);

int utf8_iswhitespace(int code);
