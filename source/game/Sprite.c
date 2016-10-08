
#include "Sprite.h"
#include "framebuffer.h"
#include "timer.h"

#define FRAME_DELAY (1000000 / 12)

void
Sprite_init(SpriteT *spr) {
	spr->enabled = 1;
	spr->frame = 0;
	for ( int i = 0; i < MAX_FRAMES; i++ ) {
		spr->frames[i] = NULL;
	}
	spr->nextFrame = timer_current() + FRAME_DELAY;
}

void
Sprite_animate(SpriteT *spr) {
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
