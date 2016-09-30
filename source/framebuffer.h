#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <sys/types.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void framebuffer_init();
uint8_t *framebuffer_getptr();
void framebuffer_clear();
void framebuffer_commit();
void framebuffer_setpal(int idx, int count, uint32_t *pal);

#endif
