
#include "framebuffer.h"
#include "Square.h"
#include "memory.h"

#define SQUARE_SZ 32

void
Square_init(SquareT *sq, int color, int x, int y) {
	sq->color = color;
	sq->x = x;
	sq->y = y;
	sq->dx = 1;
	sq->dy = 1;
}

void
Square_move(SquareT *sq) {
	sq->x += sq->dx;
	sq->y += sq->dy;
	if ( sq->x > SCREEN_WIDTH - SQUARE_SZ ) {
		sq->x = SCREEN_WIDTH - SQUARE_SZ;
		sq->dx = -1;
	}
	if ( sq->y > SCREEN_HEIGHT - SQUARE_SZ ) {
		sq->y = SCREEN_HEIGHT - SQUARE_SZ;
		sq->dy = -1;
	}
	if ( sq->x < 0 ) {
		sq->x = 0;
		sq->dx = 1;
	}
	if ( sq->y < 0 ) {
		sq->y = 0;
		sq->dy = 1;
	}
}

void
Square_draw(SquareT *sq, uint8_t *fb) {
	for ( int i = 0; i < SQUARE_SZ; i++ ) {
		for ( int j = 0; j < SQUARE_SZ; j++ ) {
			int px = i + sq->x;
			int py = j + sq->y;
			int pos = (py * SCREEN_WIDTH) + px;
			fb[pos] = sq->color;
		}
	}
}
