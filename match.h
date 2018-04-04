#ifndef MATCH
#define MATCH

#include "collections.h"

#define NUMBSIZE sizeof(numb)

typedef struct numb {
	int pos;
	List number;
	List result;
} numb, *Numb;

int startsWith(int *, int *);
int endsWith(int *, int *);
void process(int *, Numb *, int);
void loadconfig(void);
int match(int, Numb *, int);
void initNumb(Numb);

#endif
