#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <sys/types.h>
#include "config.h"

typedef struct {
	int enabled;
	uint8_t *art;
	uint8_t *frames[SPRITE_MAX_FRAMES+1];
	int frame;
	int nextFrame;
	int width, height;
	int anchorX, anchorY;
	int x, y;
} SpriteT;

void Sprite_init(SpriteT *spr);
void Sprite_setFrames(SpriteT *spr, int count, uint8_t **art);
void Sprite_animate(SpriteT *spr);
void Sprite_draw(SpriteT *spr, uint8_t *fb);

#endif
