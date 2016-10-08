#ifndef __TIMER_H__
#define __TIMER_H__

extern int timer_fps_current;

#define TIMER_SEC 1000000

uint64_t timer_current();
void timer_count_frame();

#endif
