#include "include/math.h"

// https://stackoverflow.com/a/1903975/11378941
int iSgn(int x) {
	return (0 < x) - (x < 0);
}

float fSgn(float x) {
	return (0.0f < x) - (x < 0.0f);
}
