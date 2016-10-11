#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "timer.h"

#define SQUARE_COUNT 20

#define SPRITE_FRAME_DELAY (TIMER_SEC / 6)
#define BULLET_LAUNCH_X 6
#define BULLET_LAUNCH_Y -1
#define SHIP_MOVE_DELAY (TIMER_SEC / 80)
#define MAX_SHIPBULLET 20
#define BULLET_MOVE_DELAY (TIMER_SEC / 400)
#define BULLET_MAX_X 645
#define SPRITE_MAX_FRAMES 10
#define MAX_SPRITE 200

#define MAX_ENEMY 100
#define ENEMY_DELAY (TIMER_SEC * 3)
#define ENEMY01_MOVE_LEFT_DELAY (TIMER_SEC / 100)

#define TAG_SHIP 1
#define TAG_SHIPBULLET (1 << 1)
#define TAG_SQUARE (1 << 2)
#define TAG_ENEMY (1 << 3)

static inline int checkMoveNext(uint64_t *nextMove, int delay) {
	int dt = timer_current() - *nextMove;
	if ( dt > 0 ) {
		int steps = (dt / delay) + 1;
		*nextMove += delay * steps;
		return steps;
	}
	return 0;
}

#endif
