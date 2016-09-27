#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <sys/types.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

uint8_t *framebuffer_getptr();
void framebuffer_clear();
void framebuffer_commit();

#endif
