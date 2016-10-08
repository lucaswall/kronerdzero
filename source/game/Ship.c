
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
#define SHIP_MOVE_DELAY (TIMER_SEC / 80)
#define SHIP_SHOOT_STOP (TIMER_SEC / 20)

int shipMoveY = 0;
int shipMoveNext;
int shipStopped = 0;

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
	shipMoveNext = timer_current();
}

void
Ship_update() {
	int dt = timer_current() - shipMoveNext;
	if ( dt > 0 ) {
		int dy = (dt / SHIP_MOVE_DELAY) + 1;
		shipMoveNext += SHIP_MOVE_DELAY * dy;
		if ( shipMoveY != 0 && shipStopped < timer_current() ) {
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
	shipStopped = timer_current() + SHIP_SHOOT_STOP;
}

void
Ship_moveDown() {
	shipMoveY = 1;
}

void
Ship_moveUp() {
	shipMoveY = -1;
}