#include "utf8.h"

int utf8_iswhitespace(int code) {
	if (code == 0x20)
		return 1;
	if (code >= 0x09 && code <= 0x0D)
		return 1;
	if (code == 0x85 || code == 0xA0 || code == 0x1680)
		return 1;
	if (code >= 0x2000 && code <= 0x200A)
		return 1;
	if (code == 0x2028 || code == 0x2029 || code == 0x202F || code == 0x205F || code == 0x3000)
		return 1;
	return 0;
}
