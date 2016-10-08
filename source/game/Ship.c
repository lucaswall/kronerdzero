
#include "Ship.h"
#include "SpriteManager.h"

extern uint8_t art_ship0[];
extern uint8_t art_ship1[];
extern uint8_t art_ship2[];
extern uint8_t art_ship3[];
extern uint8_t art_ship4[];

void
Ship_init() {
	SpriteT *ship = SpriteManager_newSprite();
	ship->art = art_ship0;
	ship->frames[0] = art_ship0;
	ship->frames[1] = art_ship1;
	ship->frames[2] = art_ship2;
	ship->frames[3] = art_ship3;
	ship->frames[4] = art_ship4;
	ship->frames[5] = art_ship3;
	ship->frames[6] = art_ship2;
	ship->frames[7] = art_ship1;
	ship->frames[8] = NULL;
	ship->width = 16;
	ship->height = 16;
	ship->anchorX = 8;
	ship->anchorY = 8;
	ship->x = 10;
	ship->y = 100;
}
