
#include <sys/types.h>

#include "framebuffer.h"
#include "memory.h"
#include "mt.h"
#include "timer.h"

#include "Square.h"
#include "DrawText.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Ship.h"
#include "zAssert.h"
#include "ShipBullet.h"

void InitSquares();
void MoveSquares();
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
	InitSquares();
	SpriteManager_init();
	Ship_init();
	ShipBullet_init();
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

	MoveSquares();
	ShipBullet_update();
	Ship_update();
	uint8_t *fb = framebuffer_getptr();
	framebuffer_clear();
	DrawSquares(fb);
	SpriteManager_draw(fb);
	DrawNumber(fb, 0, 5, 1, timer_fps_current);
	framebuffer_commit();
	timer_count_frame();
}

void
InitSquares() {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		int color = (i % 3) + 2;
		int x = genrand_range(10, SCREEN_WIDTH - 50);
		int y = genrand_range(10, SCREEN_HEIGHT - 50);
		Square_init(&squares[i], color, x, y);
	}
}

void
MoveSquares() {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		Square_move(&squares[i]);
	}
}

void
DrawSquares(uint8_t *fb) {
	for ( int i = 0; i < SQUARE_COUNT; i++ ) {
		Square_draw(&squares[i], fb);
	}
}
