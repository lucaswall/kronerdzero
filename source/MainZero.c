
#include <sys/types.h>

uint16_t *framebuffer_getptr();
void framebuffer_clear();
void wait_some_time(int num);

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define SQUARE_SZ 10

void MoveSquare(int *x, int *y, int *dx, int *dy);
void DrawSquare(uint16_t *fb, int x, int y);

void
MainZero() {
	uint16_t *fb = framebuffer_getptr();
	int x = 0, y = 0, dx = 1, dy = 1;
	for ( ;; ) {
		MoveSquare(&x, &y, &dx, &dy);
		framebuffer_clear();
		DrawSquare(fb, x, y);
		wait_some_time(0xffff);
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
DrawSquare(uint16_t *fb, int x, int y) {
	for ( int i = 0; i < SQUARE_SZ; i++ ) {
		for ( int j = 0; j < SQUARE_SZ; j++ ) {
			int px = i + x;
			int py = j + y;
			int pos = (py * SCREEN_WIDTH) + px;
			fb[pos] = 0xf800;
		}
	}
}
