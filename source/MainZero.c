
#include <sys/types.h>

#include "framebuffer.h"
#include "memory.h"
#include "mt.h"
#include "timer.h"

#include "Square.h"
#include "DrawText.h"

void InitSquares();
void MoveSquares();
void DrawSquares();

uint32_t colors[] = { 0xff0000ff, 0xff00ff00, 0xffff0000 };

void
MainZero() {

	framebuffer_setpal(10, 3, colors);
	framebuffer_init();
	init_genrand_with_hw();
	InitSquares();

	for ( ;; ) {
		MoveSquares();
		uint8_t *fb = framebuffer_getptr();
		framebuffer_clear();
		DrawSquares(fb);
		DrawString(fb, 300, 200, 1, "Hello WORLD!");
		DrawNumber(fb, 0, 5, 1, timer_fps_current);
		framebuffer_commit();
		timer_count_frame();
	}

}

void
InitSquares() {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		int color = (i % 3) + 10;
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
