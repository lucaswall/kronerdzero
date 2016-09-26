
#include <sys/types.h>

uint8_t *framebuffer_getptr();
void framebuffer_clear();
void framebuffer_commit();

void wait_some_time(int num);

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SQUARE_SZ 32

void MoveSquare(int *x, int *y, int *dx, int *dy);
void DrawSquare(uint8_t *fb, int x, int y);

static int test_bss;

void
MainZero() {
	int x = 0, y = 0, dx = 1, dy = 1;
	static int test2_bss;
	for ( ;; ) {

		test2_bss = test_bss + test2_bss + 1;

		MoveSquare(&x, &y, &dx, &dy);

		uint8_t *fb = framebuffer_getptr();
		framebuffer_clear();
		fb[SCREEN_WIDTH+test_bss] = 1;
		DrawSquare(fb, x, y);
		framebuffer_commit();

		//wait_some_time(0xffff);
	}
}

void
MoveSquare(int *x, int *y, int *dx, int *dy) {
	*x += *dx;
	*y += *dy;
	if ( *x > SCREEN_WIDTH - SQUARE_SZ ) {
		*x = SCREEN_WIDTH - SQUARE_SZ;
		*dx = -1;
	}
	if ( *y > SCREEN_HEIGHT - SQUARE_SZ ) {
		*y = SCREEN_HEIGHT - SQUARE_SZ;
		*dy = -1;
	}
	if ( *x < 0 ) {
		*x = 0;
		*dx = 1;
	}
	if ( *y < 0 ) {
		*y = 0;
		*dy = 1;
	}
}

void
DrawSquare(uint8_t *fb, int x, int y) {
	for ( int i = 0; i < SQUARE_SZ; i++ ) {
		for ( int j = 0; j < SQUARE_SZ; j++ ) {
			int px = i + x;
			int py = j + y;
			int pos = (py * SCREEN_WIDTH) + px;
			fb[pos] = 1;
		}
	}
}
