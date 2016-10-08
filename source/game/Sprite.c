
#include "Sprite.h"
#include "framebuffer.h"
#include "timer.h"
#include "zAssert.h"

#define FRAME_DELAY (TIMER_SEC / 12)

void
Sprite_init(SpriteT *spr) {
	spr->enabled = 1;
	spr->art = NULL;
	spr->frames[0] = NULL;
}

void
Sprite_setFrames(SpriteT *spr, int count, uint8_t **art) {
	Z_ASSERT(count <= MAX_FRAMES, "too many frames for sprite");
	for ( int i = 0; i < count; i++ ) {
		spr->frames[i] = art[i];
	}
	spr->frames[count+1] = NULL;
	spr->frame = 0;
	if ( spr->art == NULL ) {
		spr->nextFrame = timer_current() + FRAME_DELAY;
		spr->art = spr->frames[0];
	}
}

void
Sprite_animate(SpriteT *spr) {
	if ( spr->frames[0] == NULL ) return;
	if ( timer_current() >= spr->nextFrame ) {
		spr->nextFrame = timer_current() + FRAME_DELAY;
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
