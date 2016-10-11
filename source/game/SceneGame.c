
#include <sys/types.h>

#include "framebuffer.h"
#include "mt.h"
#include "timer.h"

#include "EnemySpawner.h"
#include "DrawText.h"
#include "SpriteManager.h"
#include "Ship.h"
#include "ShipBullet.h"
#include "EnemySpawner.h"

int finished;

void
SceneGame_init() {
	SpriteManager_init();
	Ship_init();
	ShipBullet_init();
	EnemySpawner_init();
	finished = 0;
}

void
SceneGame_loop() {
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

	EnemySpawner_update();
	ShipBullet_update();
	Ship_update();
	finished = EnemySpawner_enemyCount() > 50;

	uint8_t *fb = framebuffer_getptr();
	framebuffer_clear();
	SpriteManager_draw(fb);
	DrawNumber(fb, 0, 5, 1, timer_fps_current);
	framebuffer_commit();
	timer_count_frame();
}

int
SceneGame_finished() {
	return finished;
}
