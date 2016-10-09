
#include "framebuffer.h"
#include "mt.h"
#include "SpriteManager.h"
#include "Square.h"
#include "config.h"

uint8_t art_square1[] = {
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
};

uint8_t art_square2[] = {
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
};

uint8_t art_square3[] = {
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
};

uint8_t *art_squares[] = { art_square1, art_square2, art_square3 };

void Square_init(SquareT *sq, int i);
void Square_move(SquareT *sq);

SquareT squares[SQUARE_COUNT];
int squaresCount;

void
Squares_init() {
	squaresCount = 0;
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		Square_init(&squares[i], i);
	}
}

void
Squares_move() {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		if ( squares[i].enabled ) {
			Square_move(&squares[i]);
		}
	}
}

int
Squares_count() {
	return squaresCount;
}

void
Square_destroy(SquareT *square) {
	square->enabled = 0;
	square->spr->enabled = 0;
	squaresCount--;
}

void
Square_init(SquareT *sq, int i) {
	squaresCount++;
	sq->enabled = 1;
	sq->spr = SpriteManager_newSprite();
	sq->spr->tag = TAG_SQUARE;
	sq->spr->collideData = sq;
	sq->spr->art = art_squares[i % 3];
	sq->spr->width = 16;
	sq->spr->height = 16;
	sq->spr->anchorX = 8;
	sq->spr->anchorY = 8;
	sq->spr->x = genrand_range(10, SCREEN_WIDTH - 50);
	sq->spr->y = genrand_range(10, SCREEN_HEIGHT - 50);
	sq->dx = 1;
	sq->dy = 1;
}

void
Square_move(SquareT *sq) {
	sq->spr->x += sq->dx;
	sq->spr->y += sq->dy;
	if ( sq->spr->x > SCREEN_WIDTH - sq->spr->width ) {
		sq->spr->x = SCREEN_WIDTH - sq->spr->width;
		sq->dx = -1;
	}
	if ( sq->spr->y > SCREEN_HEIGHT - sq->spr->height ) {
		sq->spr->y = SCREEN_HEIGHT - sq->spr->height;
		sq->dy = -1;
	}
	if ( sq->spr->x < 0 ) {
		sq->spr->x = 0;
		sq->dx = 1;
	}
	if ( sq->spr->y < 0 ) {
		sq->spr->y = 0;
		sq->dy = 1;
	}
}
