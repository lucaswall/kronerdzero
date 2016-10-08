
#include "ShipBullet.h"
#include "SpriteManager.h"
#include "zAssert.h"
#include "timer.h"
#include "config.h"
#include "Square.h"

extern uint8_t art_ship_bullet[];

typedef struct {
	int enabled;
	int nextMove;
	SpriteT *spr;
} ShipBulletT;

ShipBulletT bullets[MAX_SHIPBULLET];

int ShipBullet_findFree();
SpriteT *ShipBullet_newSprite();
void ShipBullet_destroy(ShipBulletT *bullet);
void ShipBullet_move(ShipBulletT *bullet);
void ShipBullet_collideSquare(ShipBulletT *bullet, SquareT *square);

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
	Sprite_setCollide(bullets[idx].spr, TAG_SQUARE, (SpriteCollideCallback *) &ShipBullet_collideSquare, &bullets[idx]);
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
	bullet->tag = TAG_SHIPBULLET;
	bullet->art = art_ship_bullet;
	bullet->width = 4;
	bullet->height = 2;
	bullet->anchorX = 0;
	bullet->anchorY = 0;
	bullet->x = x;
	bullet->y = y;
	return bullet;
}

void
ShipBullet_destroy(ShipBulletT *bullet) {
	bullet->spr->enabled = 0;
	bullet->enabled = 0;
}

void
ShipBullet_move(ShipBulletT *bullet) {
	int dt = timer_current() - bullet->nextMove;
	if ( dt > 0 ) {
		int dx = (dt / BULLET_MOVE_DELAY) + 1;
		bullet->spr->x += dx;
		bullet->nextMove += BULLET_MOVE_DELAY * dx;
		if ( bullet->spr->x >= BULLET_MAX_X ) {
			ShipBullet_destroy(bullet);
		}
	}
}

void
ShipBullet_collideSquare(ShipBulletT *bullet, SquareT *square) {
	ShipBullet_destroy(bullet);
	Square_destroy(square);
}
