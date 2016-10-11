
#include "EnemySpawner.h"
#include "mt.h"
#include "art.h"
#include "framebuffer.h"
#include "zAssert.h"

EnemyT enemies[MAX_ENEMY];
uint64_t nextSpawn;

EnemyT *EnemySpawner_findFree();
SpriteT *EnemySpawner_newSprite();
void EnemySpawner_moveEnemy(EnemyT *enemy);
int enemyCount;

void
EnemySpawner_init() {
	enemyCount = 0;
	for ( int i = 0; i < MAX_ENEMY; i++ ) {
		enemies[i].enabled = 0;
	}
	nextSpawn = timer_current() + ENEMY_DELAY;
}

void
EnemySpawner_update() {
	if ( checkMoveNext(&nextSpawn, ENEMY_DELAY) > 0 ) {
		enemyCount++;
		EnemyT *enemy = EnemySpawner_findFree();
		enemy->enabled = 1;
		enemy->nextMove = timer_current();
		enemy->spr = EnemySpawner_newSprite();
		enemy->spr->collideData = enemy;
	}
	for ( int i = 0; i < MAX_ENEMY; i++ ) {
		if ( enemies[i].enabled ) {
			EnemySpawner_moveEnemy(&enemies[i]);
		}
	}
}

int
EnemySpawner_enemyCount() {
	return enemyCount;
}

void
EnemySpawner_destroy(EnemyT *enemy) {
	enemy->enabled = 0;
	enemy->spr->enabled = 0;
}

EnemyT *
EnemySpawner_findFree() {
	for ( int i = 0; i < MAX_ENEMY; i++ ) {
		if ( ! enemies[i].enabled ) {
			return &enemies[i];
		}
	}
	Z_ERROR("no more enemies in pool");
	return NULL;
}

SpriteT *
EnemySpawner_newSprite() {
	SpriteT *spr = SpriteManager_newSprite();
	Sprite_setFrames(spr, sizeof(art_enemy01_frames)/sizeof(uint8_t *), art_enemy01_frames);
	spr->tag = TAG_ENEMY;
	spr->width = art_enemy01_0_width;
	spr->height = art_enemy01_0_height;
	spr->anchorX = art_enemy01_0_width / 2;
	spr->anchorY = art_enemy01_0_height / 2;
	spr->x = SCREEN_WIDTH + spr->width / 2;
	spr->y = genrand_range(spr->height / 2, SCREEN_HEIGHT - spr->height / 2);
	return spr;
}

void
EnemySpawner_moveEnemy(EnemyT *enemy) {
	enemy->spr->x -= checkMoveNext(&enemy->nextMove, ENEMY01_MOVE_LEFT_DELAY);
	if ( enemy->spr->x < -enemy->spr->width/2 ) {
		EnemySpawner_destroy(enemy);
	}
}
