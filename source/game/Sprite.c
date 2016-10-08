
#include "Sprite.h"
#include "framebuffer.h"
#include "timer.h"
#include "zAssert.h"
#include "config.h"

void
Sprite_init(SpriteT *spr) {
	spr->enabled = 1;
	spr->art = NULL;
	spr->frames[0] = NULL;
	spr->tag = 0;
	spr->collideMask = 0;
}

void
Sprite_setFrames(SpriteT *spr, int count, uint8_t **art) {
	Z_ASSERT(count <= SPRITE_MAX_FRAMES, "too many frames for sprite");
	for ( int i = 0; i < count; i++ ) {
		spr->frames[i] = art[i];
	}
	spr->frames[count+1] = NULL;
	spr->frame = 0;
	if ( spr->art == NULL ) {
		spr->nextFrame = timer_current() + SPRITE_FRAME_DELAY;
		spr->art = spr->frames[0];
	}
}

void
Sprite_animate(SpriteT *spr) {
	if ( spr->frames[0] == NULL ) return;
	if ( timer_current() >= spr->nextFrame ) {
		spr->nextFrame = timer_current() + SPRITE_FRAME_DELAY;
		spr->frame++;
		if ( spr->frames[spr->frame] == NULL ) {
			spr->frame = 0;
		}
		spr->art = spr->frames[spr->frame];
	}
}

void
Sprite_draw(SpriteT *spr, uint8_t *fb) {
	if ( spr->art == NULL ) return;
	int px = spr->x - spr->anchorX;
	int py = spr->y - spr->anchorY;
	for ( int y = 0; y < spr->height; y++ ) {
		for ( int x = 0; x < spr->width; x++ ) {
			int sx = px + x;
			int sy = py + y;
			if ( sx >= 0 && sx < SCREEN_WIDTH && sy >= 0 && sy < SCREEN_HEIGHT ) {
				uint8_t c = spr->art[(y*spr->width)+x];
				if ( c > 0 ) {
					fb[(sy*SCREEN_WIDTH)+sx] = c;
				}
			}
		}
	}
}

void
Sprite_setCollide(SpriteT *spr, uint16_t mask, SpriteCollideCallback *callback, void *data) {
	spr->collideMask = mask;
	spr->collideCallback = callback;
	spr->collideData = data;
}

int
Sprite_overlap(SpriteT *spr1, SpriteT *spr2) {
	int spr1_minx = spr1->x - spr1->anchorX;
	int spr1_maxx = spr1->x + spr1->anchorX - 1;
	int spr1_miny = spr1->y - spr1->anchorY;
	int spr1_maxy = spr1->y + spr1->anchorY - 1;
	int spr2_minx = spr2->x - spr2->anchorX;
	int spr2_maxx = spr2->x + spr2->anchorX - 1;
	int spr2_miny = spr2->y - spr2->anchorY;
	int spr2_maxy = spr2->y + spr2->anchorY - 1;
	return spr1_maxx >= spr2_minx && spr1_minx <= spr2_maxx && spr1_maxy >= spr2_miny && spr1_miny <= spr2_maxy;
}
