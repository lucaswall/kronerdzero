
#include "Ship.h"
#include "SpriteManager.h"
#include "ShipBullet.h"
#include "timer.h"

extern uint8_t art_ship0[];
extern uint8_t art_ship1[];
extern uint8_t art_ship2[];
extern uint8_t art_ship3[];
extern uint8_t art_ship4[];

SpriteT *shipSpr;

#define BULLET_LAUNCH_X 4
#define BULLET_LAUNCH_Y -1
#define SHIP_MOVE_DELAY (TIMER_SEC / 100)

void
Ship_init() {
	uint8_t *frames[] = { art_ship0, art_ship1, art_ship2, art_ship3, art_ship4, art_ship3, art_ship2, art_ship1 };
	shipSpr = SpriteManager_newSprite();
	Sprite_setFrames(shipSpr, sizeof(frames)/sizeof(uint8_t *), frames);
	shipSpr->width = 16;
	shipSpr->height = 16;
	shipSpr->anchorX = 8;
	shipSpr->anchorY = 8;
	shipSpr->x = 10;
	shipSpr->y = 100;
}

void
Ship_shoot() {
	ShipBullet_new(shipSpr->x + BULLET_LAUNCH_X, shipSpr->y + BULLET_LAUNCH_Y);
}
