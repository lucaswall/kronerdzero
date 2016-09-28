
#include <sys/types.h>

#include "framebuffer.h"
#include "Square.h"
#include "memory.h"
#include "mt.h"

void InitSquares();
void MoveSquares();
void DrawSquares();

unsigned long temperature_get(void);

void
MainZero() {

	for ( ;; ) {
		//init_genrand(temperature_get());
		init_genrand(0);
		InitSquares();
		for ( int i = 0; i < 100; i++ ) {
			MoveSquares();
			DrawSquares();
		}
	}

}

void
InitSquares() {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		int color = (i % 3) + 1;
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
DrawSquares() {
	uint8_t *fb = framebuffer_getptr();
	framebuffer_clear();
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		Square_draw(&squares[i], fb);
	}
	framebuffer_commit();
}
