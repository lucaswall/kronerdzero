#ifndef __ENEMYSPAWNER_H__
#define __ENEMYSPAWNER_H__

#include <sys/types.h>

#include "SpriteManager.h"

typedef struct {
	int enabled;
	uint64_t nextMove;
	SpriteT *spr;
} EnemyT;

void EnemySpawner_init();
void EnemySpawner_update();
int EnemySpawner_enemyCount();
void EnemySpawner_destroy(EnemyT *enemy);

#endif
