
#include "memory.h"

SquareT squares[SQUARE_COUNT];

extern uint8_t art_ship[];

SpriteT sprShip = {
	art_ship,
	16, 16,
	8, 8,
	10, 200,
};
