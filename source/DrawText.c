
#include <sys/types.h>

#include "framebuffer.h"
#include "DrawText.h"

#include "font8x8_basic.h"

void DrawString(uint8_t *fb, int x, int y, int color, const char *str) {
	for ( ; *str; str++ ) {
		DrawChar(fb, x, y, color, *str);
		x += 8;
	}
}

void DrawNumber(uint8_t *fb, int x, int y, int color, unsigned long num) {
	char buf[100];
	int pos = 0;
	do {
		buf[pos++] = (num % 10) + 0x30;
		num /= 10;
	} while ( num > 0 && pos < 100 );
	for ( pos--; pos >= 0; pos-- ) {
		DrawChar(fb, x, y, color, buf[pos]);
		x += 8;
	}
}

void DrawChar(uint8_t *fb, int x, int y, int color, const char ch) {
	uint8_t *glyph = font8x8_basic[(unsigned char) ch];
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			if ( (glyph[i] & (1 << j)) ) {
				int px = x + j;
				int py = y + i;
				int pos = (py * SCREEN_WIDTH) + px;
				fb[pos] = color;
			}
		}
	}
}
