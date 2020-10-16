#include "include/graphics.h"
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/nearptr.h>

#define VIDEO_INTERRUPT 0x10
#define FUNC_SET_MODE 0x00
#define VGA_256_COLORMODE 0x13
#define TEXT_MODE 0x03

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

Byte* vga = (Byte*) 0xA0000;

void switchToVGA() {
	union REGS regs;
	regs.h.ah = FUNC_SET_MODE; // Function 00h == mode set
	regs.h.al = VGA_256_COLORMODE; // 256 colors
	int86(VIDEO_INTERRUPT, &regs, &regs); // Interrupt
}

void switchToText() {
	union REGS regs;
	regs.h.ah = FUNC_SET_MODE;
	regs.h.al = TEXT_MODE; // 0x03 == text mode
	int86(VIDEO_INTERRUPT, &regs, &regs);
}

void graphInit() {
	switchToVGA();
	__djgpp_nearptr_enable();
	vga += __djgpp_conventional_base;
}

void graphDeinit() {
	switchToText();
}

void graphDrawPixel(int x, int y, Byte color) {
	vga[y * SCREEN_WIDTH + x] = color;
}
