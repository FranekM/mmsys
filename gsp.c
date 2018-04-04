#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utf8.h"
#include "match.h"

#define MAXSIZE 100

int main(int argc, char *argv[]) {
	
	char *dictPath = NULL;
	
	int c = 0;
	while ((c = getopt(argc, argv, "d:")) != -1) {
		switch (c) {
			case 'd':
				dictPath = optarg;
				break;
			default:
				return 1;
		}
	}
	
	int n;
	Numb numbs[MAXSIZE];
	for (int i = optind; i < argc; i++) {
		n = i-optind;
		numbs[n] = malloc(NUMBSIZE);
		initNumb(numbs[n]);
		char *tmp = argv[i];
		while (*tmp != '\0') {
			add(numbs[n]->number, *tmp-0x30);
			tmp++;
		}
	}
	n++;
	
	if (dictPath == NULL)
		dictPath = "dict.txt";
	
	loadconfig();
	
	FILE *dict = fopen(dictPath, "r");

	int *word;
	while ((word = utf8_readword(dict)) != NULL) {
		process(word, numbs, n);
	}
	
	fclose(dict);
	
	int charset[] = {'<', 'm', 'e', 't', 'a', ' ', 'c', 'h', 'a', 'r', 's', 'e', 't', '=', '"', 'u', 't', 'f', '-', '8', '"', '>', '\0'};
	int hr[] = {'<', 'h', 'r', '>', '\0'};
	int bb[] = {'<', 'b', '>', '\0'};
	int be[] = {'<', '/', 'b', '>', '\0'};
	
	FILE *res = fopen("results.html", "w");
	utf8_writeline(res, charset);
	for (int i = 0; i < n; i++) {
		int rs = numbs[i]->result->size;
		int ns = numbs[i]->number->size;
		utf8_writeword(res, bb);
		for (int j = 0; j < ns; j++)
			utf8_write(res, get(numbs[i]->number, j)+0x30);
		utf8_writeword(res, be);
		utf8_write(res, ' ');
		for (int j = 0; j < rs; j++) {
			utf8_writeword(res, pget(numbs[i]->result, j));
			utf8_write(res, ' ');
		}
		utf8_write(res, '\n');
		utf8_writeword(res, hr);
		utf8_write(res, '\n');
	}
	
	fclose(res);
	
	printf("%d", n);
	
	return 0;
}

