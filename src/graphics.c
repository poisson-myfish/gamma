#include "include/graphics.h"
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/nearptr.h>
#include <string.h>
#include "include/math.h"

#define VIDEO_INTERRUPT 0x10
#define FUNC_SET_MODE 0x00
#define VGA_256_COLORMODE 0x13
#define TEXT_MODE 0x03
#define FUNC_SVGA 0x4f02

static Byte* vga = (Byte*) 0xA0000;

static int screenWidth;
static int screenHeight;

void switchMode(Byte mode) {
	union REGS regs;
	regs.h.ah = FUNC_SET_MODE;
	regs.h.al = mode;
	int86(VIDEO_INTERRUPT, &regs, &regs);
}

void superVGAMode(Word resolution) {  // Needs some work to deal with SVGA correctly
	union REGS regs;
	regs.w.ax = FUNC_SVGA;
	regs.w.bx = resolution;
	int86(VIDEO_INTERRUPT, &regs, &regs);
}

void graphInit() {
	switchMode(VGA_256_COLORMODE);
	__djgpp_nearptr_enable();
	vga += __djgpp_conventional_base;

	screenWidth = 320;
	screenHeight = 200;
}

void graphDeinit() {
	switchMode(TEXT_MODE);
}

void graphSwitchResolution(Word res) {
	superVGAMode(res);
	
	switch (res) {
	case RES_640x480:
		screenWidth = 640;
		screenHeight = 480;
		break;
		
	case RES_800x600:
		screenWidth = 800;
		screenHeight = 600;
		break;

	case RES_1024x768:
		screenWidth = 1024;
		screenHeight = 768;
		break;
	}
}

void graphDrawPixel(int x, int y, Byte color) {
	vga[y * screenWidth + x] = color;
}

void graphDrawLine(int x1, int y1, int x2, int y2, Byte color) {
	int distX = x2 - x1;
	int distY = y2 - y1;

	int distXAbs = abs(distX);
	int distYAbs = abs(distY);

	int signDistX = iSgn(distX);
	int signDistY = iSgn(distY);

	 // This means that the general direction of the line is horizontal
	if (distXAbs >= distYAbs) {
		float slope = (float)distY / (float)distX;
		for (int i = 0; i != distX; i += signDistX) {
			int pixelX = i + x1;
			int pixelY = slope * i + y1;
			graphDrawPixel(pixelX, pixelY, color);
		}
	} else {  // This means that the line's general direction is vertical
		float slope = (float)distX / (float)distY;
		for (int i = 0; i != distY; i += signDistY) {
			int pixelX = slope * i + x1;
			int pixelY = i + y1;
			graphDrawPixel(pixelX, pixelY, color);
		}
	}
}

void graphDrawRect(int topX, int topY, int bottomX, int bottomY, Byte color) {
    graphDrawLine(topX, topY, topX, bottomY, color);  // Draw left
	graphDrawLine(topX, bottomY, bottomX, bottomY, color);  // Draw bottom
	graphDrawLine(topX, topY, bottomX, topY, color);  // Draw top
	graphDrawLine(bottomX, topY, bottomX, bottomY, color);  // Draw Right
}


void graphFillRect(int topX, int topY, int bottomX, int bottomY, Byte color) {
  Word temp;

  if (topY > bottomY) {
    temp = topY;
    topY = bottomY;
    bottomY = temp;
  }
  
  if (topX > bottomX) {
    temp = topX;
    topX = bottomX;
    bottomX = temp;
  }

  Word topOffset = (topY << 8)+(topY << 6) + topX;
  Word bottomOffset = (bottomY << 8)+(bottomY << 6) + topX;
  Word width = bottomX - topX + 1;

  for(Word i = topOffset; i <= bottomOffset; i += screenWidth) {
    memset(&vga[i], color, width - 1);
  }
}
