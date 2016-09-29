
#include <sys/types.h>

#include "framebuffer.h"
#include "memory.h"
#include "mt.h"

#include "Square.h"
#include "DrawText.h"

void InitSquares();
void MoveSquares();
void DrawSquares();

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
			DrawNumber(fb, 10, 10, 1, 2637829104);
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
