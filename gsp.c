#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <>

int main(int argc, char *argv[]) {
	
	char *dictPath;
	int limit = -1;
	bool ignore1 = false;
	
	int c = 0;
	
	while ((c = getopt(argc, argv, "d:l:1")) != -1) {
		
		switch (c) {
			case 'd':
				dictPath = optarg;
				break;
			case 'l':
				limit = atoi(optarg);
				break;
			case '1':
				ignore1 = true;
				break;
			default:
				return 1;			
		}
		
	}
	
	if (dict == NULL)
		return 1;
		
	if (limit == 0)
		return 0;
	
	FILE *dict = fopen(dictPath, "r");

	int cp;
	while ((cp = getcp(file)) != EOF) {
		
	}
	
	fclose(dict);
	
	return 0;
}

