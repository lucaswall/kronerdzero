
#include "Ship.h"
#include "SpriteManager.h"
#include "ShipBullet.h"
#include "timer.h"
#include "config.h"

extern uint8_t art_ship0[];
extern uint8_t art_ship1[];
extern uint8_t art_ship2[];
extern uint8_t art_ship3[];
extern uint8_t art_ship4[];

SpriteT *shipSpr;

int shipMoveY;
uint64_t shipMoveNext;

void
Ship_init() {
	uint8_t *frames[] = { art_ship0, art_ship1, art_ship2, art_ship3, art_ship4, art_ship3, art_ship2, art_ship1 };
	shipSpr = SpriteManager_newSprite();
	Sprite_setFrames(shipSpr, sizeof(frames)/sizeof(uint8_t *), frames);
	shipSpr->tag = TAG_SHIP;
	shipSpr->width = 16;
	shipSpr->height = 16;
	shipSpr->anchorX = 8;
	shipSpr->anchorY = 8;
	shipSpr->x = 10;
	shipSpr->y = 100;
	shipMoveY = 0;
	shipMoveNext = timer_current();
}

void
Ship_update() {
	int64_t dt = timer_current() - shipMoveNext;
	if ( dt > 0 ) {
		int dy = (dt / SHIP_MOVE_DELAY) + 1;
		shipMoveNext += SHIP_MOVE_DELAY * dy;
		if ( shipMoveY != 0 ) {
			shipSpr->y += shipMoveY > 0 ? dy : -dy;
			shipMoveY = 0;
		}
	}
}

int
Ship_posY() {
	return shipSpr->y;
}

void
Ship_shoot() {
	ShipBullet_new(shipSpr->x + BULLET_LAUNCH_X, shipSpr->y + BULLET_LAUNCH_Y);
}

void
Ship_moveDown() {
	shipMoveY = 1;
}

void
Ship_moveUp() {
	shipMoveY = -1;
}
