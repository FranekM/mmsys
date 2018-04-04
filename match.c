#include <stdlib.h>
#include <stdio.h>
#include "utf8.h"
#include "match.h"
#include "collections.h"
#include "match.h"

#define MAXITERATION 100

static void swap(Numb *, int, int);
static int islast(Numb);
static int *map[10];

int match(int letter, Numb *numbs, int n) {
	int newlen = n;
	while (--n >= 0) {
		//printf("\ndigit: %d\n", get(numbs[n]->number, numbs[n]->pos));
		int *row = map[get(numbs[n]->number, numbs[n]->pos)];
		for (int i = 0; row[i] != '\0' && i < MAXITERATION; i++) {
			//printf("%d, %d | ", letter, row[i]);
			if (letter == row[i]) {
				//printf("%d LETTER MATCHED!\n", get(numbs[n]->number, numbs[n]->pos));
				(numbs[n]->pos)++;
				if (islast(numbs[n])) {
					newlen--;
					swap(numbs, n, newlen);
					//printf("WORD MATCHED!\n");
				}
				break;
			}
		}
		//printf("\n");
	}
	return newlen;
}

void swap(Numb *tab, int a, int b) {
	Numb c = tab[a];
	tab[a] = tab[b];
	tab[b] = c;
}

int islast(Numb numb) {
	return numb->pos >= numb->number->size;
}

int startsWith(int *word, int *start) {
	for (int i = 0; start[i] != '\0'; i++)
		if (word[i] != start[i])
			return 0;
	return 1;
}

int endsWith(int *word, int *end) {
	int i;
	while (word[i] != '\0')
		i++;
	while (--i > 0)
		if (word[i] != end[i])
			return 0;
	return 1;
}

void process(int *word, Numb *numbs, int n) {
	int newlen = n;
	for (int i = 0; i < word[i] != '\0'; i++)
		newlen = match(word[i], numbs, newlen);
	if (newlen == n)
		free(word);
	for (int i = 0; i < n; i++)
		numbs[i]->pos = 0;
	for (int i = newlen; i < n; i++)
		padd(numbs[i]->result, word);
}

void initNumb(Numb numb) {
	List number = malloc(LISTSIZE);
	List result = malloc(LISTSIZE);
	initList(number, "int");
	initList(result, "int *");
	numb->number = number;
	numb->result = result;
	numb->pos = 0;
}

void loadconfig() {
	FILE *f = fopen("itoa.conf", "r");
	for (int i = 0; i < 10; i++)
		map[i] = utf8_readline(f);
	fclose(f);
}
