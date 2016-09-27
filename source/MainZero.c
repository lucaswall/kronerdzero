
#include <sys/types.h>

#include "framebuffer.h"
#include "Square.h"
#include "memory.h"

void
MainZero() {
	int x = 0, y = 0, dx = 1, dy = 1;

	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		int color = (i % 3) + 1;
		int x = i * 50;
		int y = i * 20;
		Square_init(&squares[i], color, x, y);
	}

	for ( ;; ) {

		for ( int i = 0; i < SQUARE_COUNT; i++ ) {
			Square_move(&squares[i]);
		}

		uint8_t *fb = framebuffer_getptr();
		framebuffer_clear();
		for ( int i = 0; i < SQUARE_COUNT; i++ ) {
			Square_draw(&squares[i], fb);
		}
		framebuffer_commit();

	}

}
