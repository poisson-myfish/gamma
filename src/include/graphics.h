#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef unsigned char Byte;
typedef unsigned short Word;

void graphInit();
void graphDeinit();

void graphDrawPixel(int x, int y, Byte color);

#endif
