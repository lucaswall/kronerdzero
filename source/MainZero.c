
#include <sys/types.h>

#include "framebuffer.h"
#include "Square.h"
#include "memory.h"
#include "mt.h"

void
MainZero() {

	init_genrand(1976);

	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		int color = (i % 3) + 1;
		int x = genrand_range(10, SCREEN_WIDTH - 50);
		int y = genrand_range(10, SCREEN_HEIGHT - 50);
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
