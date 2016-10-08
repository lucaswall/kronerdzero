
#include <sys/types.h>

#include "framebuffer.h"
#include "mt.h"
#include "timer.h"

#include "Square.h"
#include "DrawText.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Ship.h"
#include "zAssert.h"
#include "ShipBullet.h"

void DrawSquares();
void GameInit();
void GameLoop();

void
MainZero() {
	GameInit();
	for ( ;; ) {
		GameLoop();
	}
}

void
GameInit() {
	framebuffer_init();
	init_genrand_with_hw();
	SpriteManager_init();
	Ship_init();
	ShipBullet_init();
	Squares_init();
}

void
GameLoop() {
	static int shoot = 0;
	static int shipDir = 1;
	if ( shoot++ > 30 ) {
		shoot = 0;
		Ship_shoot();
	}
	if ( Ship_posY() < 10 ) shipDir = 1;
	if ( Ship_posY() > 470 ) shipDir = -1;
	if ( shipDir > 0 ) Ship_moveDown();
	else Ship_moveUp();

	Squares_move();
	ShipBullet_update();
	Ship_update();

	uint8_t *fb = framebuffer_getptr();
	framebuffer_clear();
	SpriteManager_draw(fb);
	DrawNumber(fb, 0, 5, 1, timer_fps_current);
	framebuffer_commit();
	timer_count_frame();
}

