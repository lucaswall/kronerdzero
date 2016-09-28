#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <sys/types.h>

typedef struct {
	int color;
	int x, y;
	int dx, dy;
} SquareT;

void Square_init(SquareT *sq, int color, int x, int y);
void Square_move(SquareT *sq);
void Square_draw(SquareT *sq, uint8_t *fb);

#endif
