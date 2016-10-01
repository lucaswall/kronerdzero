#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <sys/types.h>

typedef struct {
	uint8_t *art;
	int width, height;
	int anchorX, anchorY;
	int x, y;
} SpriteT;

void Sprite_draw(SpriteT *spr, uint8_t *fb);

#endif
