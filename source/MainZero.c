
#include <sys/types.h>

#include "framebuffer.h"
#include "Square.h"
#include "memory.h"
#include "mt.h"
#include "font8x8_basic.h"

void InitSquares();
void MoveSquares();
void DrawSquares();
void DrawString(uint8_t *fb, int x, int y, int color, const char *str);

void
MainZero() {

	for ( ;; ) {
		init_genrand_with_hw();
		InitSquares();
		for ( int i = 0; i < 100; i++ ) {
			MoveSquares();
			uint8_t *fb = framebuffer_getptr();
			framebuffer_clear();
			DrawSquares(fb);
			DrawString(fb, 300, 200, 1, "Hello WORLD!");
			framebuffer_commit();
		}
	}

}

void
InitSquares() {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		int color = (i % 3) + 2;
		int x = genrand_range(10, SCREEN_WIDTH - 50);
		int y = genrand_range(10, SCREEN_HEIGHT - 50);
		Square_init(&squares[i], color, x, y);
	}
}

void
MoveSquares() {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		Square_move(&squares[i]);
	}
}

void
DrawSquares(uint8_t *fb) {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		Square_draw(&squares[i], fb);
	}
}

void DrawString(uint8_t *fb, int x, int y, int color, const char *str) {
	for ( ; *str; str++ ) {
		uint8_t *glyph = font8x8_basic[(unsigned char) *str];
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
		x += 8;
	}
}
