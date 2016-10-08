
#include "stringsupport.h"

char *
StringCopy(char *dst, const char *src) {
	while ( *src ) {
		*(dst++) = *(src++);
	}
	*dst = 0;
	return dst;
}

char *
StringFromInt(char *dst, int num) {
	char buf[100];
	int pos = 0;
	do {
		buf[pos++] = (num % 10) + 0x30;
		num /= 10;
	} while ( num > 0 && pos < 100 );
	for ( pos--; pos >= 0; pos-- ) {
		*(dst++) = buf[pos];
	}
	*dst = 0;
	return dst;
}
