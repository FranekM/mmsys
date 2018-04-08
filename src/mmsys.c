#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utf8.h"
#include "match.h"

#define MAXSIZE 100

static void showHelp(void);

int main(int argc, char *argv[]) {
	
	char *dictPath = NULL;
	
	int c = 0;
	while ((c = getopt(argc, argv, "d:h")) != -1) {
		switch (c) {
			case 'd':
				dictPath = optarg;
				break;
			case 'h':
				showHelp();
				return 0;
			default:
				return 1;
		}
	}

	if (optind >= argc) {
		showHelp();
		return 0;
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
	
	int total = 0;
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
			total++;
		}
		utf8_write(res, '\n');
		utf8_writeword(res, hr);
		utf8_write(res, '\n');
	}
	
	fclose(res);
	
	printf("%d found and saved in results.html", total);
	
	return 0;
}

void showHelp() {
	printf("Hi, this is a program to encode numbers using mnemonic major system\n");
	printf("in order to encode some numbers use following syntax:\n\n");
	printf("\tmmsys [[number] [number] ...]\n");
	printf("\tmmsys 1410 2018 12 3\n\n");
	printf("the results will be saved in results.html file\n\n");
	printf("For more help see HELP.txt\n");
	printf("Thnaks for using my program - Bartosz Mierzwa");
}