
#include "Ship.h"
#include "SpriteManager.h"
#include "ShipBullet.h"
#include "timer.h"
#include "config.h"
#include "art.h"

SpriteT *shipSpr;
int shipMoveY;
uint64_t shipMoveNext;

void
Ship_init() {
	shipSpr = SpriteManager_newSprite();
	Sprite_setFrames(shipSpr, sizeof(art_heroship_frames)/sizeof(uint8_t *), art_heroship_frames);
	shipSpr->tag = TAG_SHIP;
	shipSpr->width = art_heroship0_width;
	shipSpr->height = art_heroship0_height;
	shipSpr->anchorX = art_heroship0_width / 2;
	shipSpr->anchorY = art_heroship0_height / 2;
	shipSpr->x = 10;
	shipSpr->y = 100;
	shipMoveY = 0;
	shipMoveNext = timer_current();
}

void
Ship_update() {
	int dy = checkMoveNext(&shipMoveNext, SHIP_MOVE_DELAY);
	if ( dy > 0 && shipMoveY != 0 ) {
		shipSpr->y += shipMoveY > 0 ? dy : -dy;
		shipMoveY = 0;
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
