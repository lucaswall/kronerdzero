#ifndef __ZASSERT_H__
#define __ZASSERT_H__

#define zAssert(cond) { if ( ! cond ) { zAssert_set(__FILE__, __LINE__, __FUNCTION__, #cond); } }

void zAssert_set(const char *file, int line, const char *function, const char *cond);

#endif
