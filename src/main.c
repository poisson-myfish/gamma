#include "include/graphics.h"

int main() {
	graphInit();
	graphDrawPixel(0, 0, 1);

	while (1) {}
	graphDeinit();
	
	return 0;
}
