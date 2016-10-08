#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <sys/types.h>
#include "config.h"

typedef void SpriteCollideCallback(void *dataOurs, void *dataOther);

typedef struct {
	int enabled;
	uint8_t *art;
	uint8_t *frames[SPRITE_MAX_FRAMES+1];
	int frame;
	int nextFrame;
	int width, height;
	int anchorX, anchorY;
	int x, y;
	uint16_t tag;
	uint16_t collideMask;
	SpriteCollideCallback *collideCallback;
	void *collideData;
} SpriteT;

void Sprite_init(SpriteT *spr);
void Sprite_setFrames(SpriteT *spr, int count, uint8_t **art);
void Sprite_animate(SpriteT *spr);
void Sprite_draw(SpriteT *spr, uint8_t *fb);
void Sprite_setCollide(SpriteT *spr, uint16_t mask, SpriteCollideCallback *callback, void *data);
int Sprite_overlap(SpriteT *spr1, SpriteT *spr2);

#endif
