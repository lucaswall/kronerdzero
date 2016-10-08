
#include "ShipBullet.h"
#include "SpriteManager.h"
#include "zAssert.h"
#include "timer.h"

#define MAX_SHIPBULLET 20
#define BULLET_MOVE_DELAY (TIMER_SEC / 400)
#define BULLET_MAX_X 645

extern uint8_t art_ship_bullet[];

typedef struct {
	int enabled;
	int nextMove;
	SpriteT *spr;
} ShipBulletT;

ShipBulletT bullets[MAX_SHIPBULLET];

int ShipBullet_findFree();
SpriteT *ShipBullet_newSprite();
void ShipBullet_move(ShipBulletT *bullet);

void
ShipBullet_init() {
	for ( int i = 0; i < MAX_SHIPBULLET; i++ ) {
		bullets[i].enabled = 0;
	}
}

void
ShipBullet_new(int x, int y) {
	int idx = ShipBullet_findFree();
	if ( idx < 0 ) return;
	bullets[idx].enabled = 1;
	bullets[idx].nextMove = timer_current();
	bullets[idx].spr = ShipBullet_newSprite(x, y);
}

void
ShipBullet_update() {
	for ( int i = 0; i < MAX_SHIPBULLET; i++ ) {
		if ( bullets[i].enabled ) {
			ShipBullet_move(&bullets[i]);
		}
	}
}

int
ShipBullet_findFree() {
	int idx = -1;
	for ( int i = 0; i < MAX_SHIPBULLET; i++ ) {
		if ( ! bullets[i].enabled ) {
			idx = i;
			break;
		}
	}
	if ( idx == -1 ) {
		Z_ERROR("no more bullets in pool");
	}
	return idx;
}

SpriteT *
ShipBullet_newSprite(int x, int y) {
	SpriteT *bullet = SpriteManager_newSprite();
	bullet->art = art_ship_bullet;
	bullet->width = 2;
	bullet->height = 2;
	bullet->anchorX = 0;
	bullet->anchorY = 0;
	bullet->x = x;
	bullet->y = y;
	return bullet;
}

void
ShipBullet_move(ShipBulletT *bullet) {
	int dt = timer_current() - bullet->nextMove;
	if ( dt > 0 ) {
		int dx = (dt / BULLET_MOVE_DELAY) + 1;
		bullet->spr->x += dx;
		bullet->nextMove += BULLET_MOVE_DELAY * dx;
		if ( bullet->spr->x >= BULLET_MAX_X ) {
			bullet->spr->enabled = 0;
			bullet->enabled = 0;
		}
	}
}
