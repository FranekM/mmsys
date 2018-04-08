#include <stdlib.h>
#include <stdio.h>
#include "utf8.h"
#include "match.h"
#include "collections.h"
#include "match.h"

static int islast(Numb);
static Tree map;

void match(int letter, Numb *numbs, int n) {
	int mapped = tget(map, letter);
	if (!isexact())
		return;
	while (--n >= 0) {
		int digit = get(numbs[n]->number, numbs[n]->pos);
		if (digit == mapped)
			(numbs[n]->pos)++;
		else
			numbs[n]->exclude = 1;
	}
}

int islast(Numb numb) {
	return numb->pos == numb->number->size;
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
	for (int i = 0; i < word[i] != '\0'; i++)
		match(word[i], numbs, n);
	for (int i = 0; i < n; i++) {
		if (!(numbs[i]->exclude) && islast(numbs[i]))
			padd(numbs[i]->result, word);
		numbs[i]->exclude = 0;
		numbs[i]->pos = 0;
	}
}

void initNumb(Numb numb) {
	List number = malloc(LISTSIZE);
	List result = malloc(LISTSIZE);
	initList(number, "int");
	initList(result, "int *");
	numb->number = number;
	numb->result = result;
	numb->exclude = 0;
	numb->pos = 0;
}

void loadconfig() {
	map = malloc(TREESIZE);
	initTree(map);
	FILE *f = fopen("itoa.conf", "r");
	int *line;
	int n = 0;
	while ((line = utf8_readline(f)) != NULL) {
		for (int i = 0; line[i] != '\0'; i++)
			tput(map, line[i], n);	
		free(line);
		n++;	
	}
	fclose(f);
}
