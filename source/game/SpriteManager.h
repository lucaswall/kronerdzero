#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include <sys/types.h>

#include "Sprite.h"

void SpriteManager_init();
SpriteT *SpriteManager_newSprite();
void SpriteManager_draw(uint8_t *fb);
void SpriteManager_checkCollide(SpriteT *spr);

#endif
