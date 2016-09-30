#ifndef __DRAWTEXT_H__
#define __DRAWTEXT_H__

void DrawString(uint8_t *fb, int x, int y, int color, const char *str);
void DrawNumber(uint8_t *fb, int x, int y, int color, unsigned long num);
void DrawNumber64(uint8_t *fb, int x, int y, int color, unsigned long long num);
void DrawChar(uint8_t *fb, int x, int y, int color, const char ch);

#endif
