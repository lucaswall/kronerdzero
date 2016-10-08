#ifndef __ZASSERT_H__
#define __ZASSERT_H__

#define Z_ASSERT(cond, explain) { if ( ! (cond) ) { zAssert_set(__FILE__, __LINE__, __FUNCTION__, #cond, explain); } }

void zAssert_set(const char *file, int line, const char *function, const char *cond, const char *explain);

#endif
