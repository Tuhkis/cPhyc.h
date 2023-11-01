#include <stdio.h>

#define CPHYC_IMPL
#include "cPhyc.h"

int main() {
	cph::Rect r1 = (cph::Rect) {0, 0, 64, 64};
	cph::Rect r2[] = { (cph::Rect) {128, 0, 64, 64} };

	for ( int i = 0; i < 10; i++ ) {
		cph::moveAndCollide(&r1, r2, 1, 16, 0);
		printf("X Pos: %f\n", r1.x);
		if (cph::isOnWall(r1, r2, 1))
			printf("Is on wall!\n");
	}

	return 0;
}
