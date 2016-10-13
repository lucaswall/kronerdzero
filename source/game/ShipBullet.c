
#include "ShipBullet.h"
#include "SpriteManager.h"
#include "zAssert.h"
#include "timer.h"
#include "config.h"
#include "art.h"
#include "EnemySpawner.h"

typedef struct {
	int enabled;
	uint64_t nextMove;
	SpriteT *spr;
} ShipBulletT;

ShipBulletT bullets[MAX_SHIPBULLET];

int ShipBullet_findFree();
SpriteT *ShipBullet_newSprite();
void ShipBullet_destroy(ShipBulletT *bullet);
void ShipBullet_move(ShipBulletT *bullet);
void ShipBullet_collideEnemy(ShipBulletT *bullet, EnemyT *enemy);

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
	Sprite_setCollide(bullets[idx].spr, TAG_ENEMY, (SpriteCollideCallback *) &ShipBullet_collideEnemy, &bullets[idx]);
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
	bullet->art = art_herobullet;
	bullet->width = art_herobullet_width;
	bullet->height = art_herobullet_height;
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
	bullet->spr->x += checkMoveNext(&bullet->nextMove, BULLET_MOVE_DELAY);
	if ( bullet->spr->x >= BULLET_MAX_X ) {
		ShipBullet_destroy(bullet);
	}
}

void
ShipBullet_collideEnemy(ShipBulletT *bullet, EnemyT *enemy) {
	ShipBullet_destroy(bullet);
	EnemySpawner_hit(enemy);
}
