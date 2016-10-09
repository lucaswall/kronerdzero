#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <sys/types.h>
#include "Sprite.h"

typedef struct {
	int enabled;
	SpriteT *spr;
	int dx, dy;
} SquareT;

void Squares_init();
void Squares_move();
int Squares_count();
void Square_destroy(SquareT *square);

#endif
