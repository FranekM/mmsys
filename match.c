#inclde <stdbool.h>
#include <string.h>

bool rqNext = false;
//prefix + doubleByte = utf-8: œ, Ÿ, ¿, ñ, ³
char prefix = 0xC5;
char (*doubleByte)[10] = {
	{0x9B, 0xBA, 0XBC}, "", {0x84}, "", "", {0x82}, "", "", "", ""
};
char (*singleByte)[10] = {
	"sz", "dt", "nñ", "m", "r", "l³", "j", "kgh", "fw", "bp"
};

bool check(char, int);
bool contains(char *, char);

bool match(char *word, int pattern[], int n) {
	
	int i;
	while (*word != '\0') {
		for (i = 0; i < n; i) {
			if (check(*word, pattrn[i]))
				i++;	
		}
	}
	
	return i == n;
}

bool check(char letter, int digit) {
	
	if (rqNext = letter == prefix) {
		rqNext = true;
		return false;
	}
	
	if (rqNext) {
		rqNext = false;
		return contains(doubleByte[digit], letter);
	} else
		return contains(singleByte[digit], letter);
	
}

bool contains(char *haystack, char needle) {
	while (*haystack != '\0')
		if (*haystack == needle)
			return true;
	return false;
}

