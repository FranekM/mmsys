#include <stdio.h>
#include "utf8.h"

int *map[10];

void loadconfig(void);



void loadconfig(void) {
	FILE *f = fopen("itoa.conf", "r");
	for (int i = 0; i < 10; i++)
		map[i] = utf8_readline(f);
	fclose(f);
}
