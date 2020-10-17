#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef unsigned char Byte;
typedef unsigned short Word;

void graphInit();
void graphDeinit();
void graphSwitchResolution(Word res);

void graphDrawPixel(int x, int y, Byte color);
void graphDrawLine(int x1, int y1, int x2, int y2, Byte color);

#define RES_640x480 0x100
#define RES_800x600 0x103
#define RES_1024x768 0x105

#endif
