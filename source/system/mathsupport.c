
#include "mathsupport.h"

extern int sine_table[256];

int
sine(int ang) {
	return sine_table[(ang+64) & 0xff];
}

int
cosine(int ang) {
	return sine_table[ang & 0xff];
}
