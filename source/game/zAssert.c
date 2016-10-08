
#include "zAssert.h"
#include "stringsupport.h"
#include "framebuffer.h"
#include "timer.h"
#include "DrawText.h"

void
zAssert_set(const char *file, int line, const char *function, const char *cond, const char *explain) {
	char assertMsg[200];
	char *msg = StringCopy(assertMsg, file);
	msg = StringCopy(msg, ":");
	msg = StringFromInt(msg, line);
	msg = StringCopy(msg, ": ");
	msg = StringCopy(msg, function);
	msg = StringCopy(msg, ": ");
	msg = StringCopy(msg, cond);
	uint8_t *fb = framebuffer_getptr();
	DrawStringBoxed(fb, 0, 5, 1, assertMsg);
	DrawStringBoxed(fb, 0, 20, 1, explain);
	framebuffer_commit();
	for ( ;; ) {}
}
