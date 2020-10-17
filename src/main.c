#include <conio.h>
#include "include/graphics.h"
#include <stdio.h>

int main() {
	graphInit();
	graphSwitchResolution(RES_800x600);
	
	//graphDrawPixel(0, 0, 1);
	//graphDrawPixel(100, 100, 2);
	graphDrawLine(0, 0, 100, 100, 3);
	
	char key;
	while (1) {
		if (kbhit()) {
			key = getch();
			if (key == 0x1b)
				break;
		}
	}
	graphDeinit();
	
	return 0;
}
