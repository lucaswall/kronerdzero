
#include "Sprite.h"
#include "framebuffer.h"

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
