
#include "Ship.h"
#include "SpriteManager.h"

extern uint8_t art_ship0[];
extern uint8_t art_ship1[];
extern uint8_t art_ship2[];
extern uint8_t art_ship3[];
extern uint8_t art_ship4[];

void
Ship_init() {
	uint8_t *frames[] = { art_ship0, art_ship1, art_ship2, art_ship3, art_ship4, art_ship3, art_ship2, art_ship1 };
	SpriteT *ship = SpriteManager_newSprite();
	Sprite_setFrames(ship, sizeof(frames)/sizeof(uint8_t *), frames);
	ship->width = 16;
	ship->height = 16;
	ship->anchorX = 8;
	ship->anchorY = 8;
	ship->x = 10;
	ship->y = 100;
}
