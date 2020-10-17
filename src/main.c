#include <conio.h>
#include "include/graphics.h"
#include <stdio.h>

int main() {
	graphInit();

	graphFillRect(0, 0, 320, 5, 24);
	
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
