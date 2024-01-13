#include <stdio.h>

#define CPHYC_IMPL
#include "cPhyc.h"

int main() {
	cph_Rect r1 = (cph_Rect) {0, 0, 64, 64};
	cph_Rect r2[] = { (cph_Rect) {128, 0, 64, 64} };

  int i;
	for ( i = 0; i < 10; i++ ) {
		cph_moveAndCollide(&r1, r2, 1, 16, 0);
		printf("X Pos: %f\n", r1.x);
		if (cph_isOnWall(r1, r2, 1) == cph_TRUE)
			printf("Is on wall!\n");
	}

	return 0;
}
