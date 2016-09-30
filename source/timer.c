
#include <sys/types.h>

#define HW_TIMER_BASE 0x3F003000
#define HW_TIMER_COUNTER 0x04

uint64_t *timer_counter = (uint64_t *) (HW_TIMER_BASE + HW_TIMER_COUNTER);

uint64_t timer_last_fps_check = 0;
int timer_fps_count = 0;
int timer_fps_current = 0;

uint64_t
timer_current() {
	return *timer_counter;
}

void
timer_count_frame() {
	timer_fps_count++;
	uint64_t elapsed = *timer_counter - timer_last_fps_check;
	if ( elapsed >= 1000000 ) {
		timer_fps_current = timer_fps_count;
		timer_fps_count = 0;
		timer_last_fps_check = *timer_counter;
	}
}
