#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "timer.h"

#define SQUARE_COUNT 20

#define SPRITE_FRAME_DELAY (TIMER_SEC / 12)
#define BULLET_LAUNCH_X 6
#define BULLET_LAUNCH_Y -1
#define SHIP_MOVE_DELAY (TIMER_SEC / 80)
#define MAX_SHIPBULLET 20
#define BULLET_MOVE_DELAY (TIMER_SEC / 400)
#define BULLET_MAX_X 645
#define SPRITE_MAX_FRAMES 10
#define MAX_SPRITE 200

#endif
