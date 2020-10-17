#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef unsigned char Byte;
typedef unsigned short Word;

void graphInit();
void graphDeinit();
void graphSwitchResolution(Word res);  // Needs some work to deal with SVGA correctly, don't use it. See bank switching

void graphDrawPixel(int x, int y, Byte color);
void graphDrawLine(int x1, int y1, int x2, int y2, Byte color);
void graphDrawRect(int topX, int topY, int bottomX, int bottomY, Byte color);
void graphFillRect(int topX, int topY, int bottomX, int bottomY, Byte color);

#define RES_640x480 0x100
#define RES_800x600 0x103
#define RES_1024x768 0x105

#endif
