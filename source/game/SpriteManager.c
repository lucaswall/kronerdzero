
#include "SpriteManager.h"
#include "zAssert.h"
#include "config.h"
#include "timer.h"
#include "mt.h"

SpriteT sprites[MAX_SPRITE];
uint64_t shakeStop;

void
SpriteManager_init() {
	for ( int i = 0; i < MAX_SPRITE; i++ ) {
		sprites[i].enabled = 0;
	}
	shakeStop = 0;
}

SpriteT *
SpriteManager_newSprite() {
	for ( int i = 0; i < MAX_SPRITE; i++ ) {
		if ( ! sprites[i].enabled ) {
			Sprite_init(&sprites[i]);
			return &sprites[i];
		}
	}
	Z_ERROR("no more sprites in pool");
	return NULL;
}

void
SpriteManager_draw(uint8_t *fb) {
	int offsetx = 0, offsety = 0;
	if ( timer_current() <= shakeStop ) {
		offsetx = genrand_range(-SCREEN_SHAKE_AMPLITUDE, SCREEN_SHAKE_AMPLITUDE);
		offsety = genrand_range(-SCREEN_SHAKE_AMPLITUDE, SCREEN_SHAKE_AMPLITUDE);
	}
	for ( int i = 0; i < MAX_SPRITE; i++ ) {
		if ( sprites[i].enabled ) {
			Sprite_animate(&sprites[i]);
			SpriteManager_checkCollide(&sprites[i]);
			if ( sprites[i].enabled ) {
				Sprite_draw(&sprites[i], fb, offsetx, offsety);
			}
		}
	}
}

void
SpriteManager_checkCollide(SpriteT *spr) {
	if ( spr->collideMask != 0 ) {
		for ( int i = 0; i < MAX_SPRITE; i++ ) {
			if ( sprites[i].enabled && &sprites[i] != spr && (sprites[i].tag & spr->collideMask) == sprites[i].tag ) {
				if ( Sprite_overlap(spr, &sprites[i]) ) {
					(*spr->collideCallback)(spr->collideData, sprites[i].collideData);
					return;
				}
			}
		}
	}
}

void
SpriteManager_screenShake(uint64_t duration) {
	shakeStop = timer_current() + duration;
}
