/*
 * File: cPhyc.h
 * Author: Nico Lindström
 * Copyright: (c) 2022-2024 Nico Lindström
 *
 * This is a header only library for AABB based physics
 * that is compatible with C89 and C++.
 *
 * ------------------------------------------------------
 *
 * Documentation:
 *   Types:
 *     Bool
 *       If you don't know what this is you should learn programming. Possible values TRUE and FALSE.
 *
 *     Rect
 *       A rectangle structure that stores its position and dimensions as 32 bit ints.
 *
 *   Methods:
 *     collideRect(rect1, rect2)
 *       Checks if two Rect's overlap.
 *
 *     moveAndCollide(rect, tiles, tilesLen, velx, vely)
 *       Moves provided Rect pointer by velx and vely and will not go through tiles, provided tilesLen (The length of the tiles array) is provided.
 *
 *     isOnFloor(rect, tiles, tilesLen)
 *       Returns a bool if the rect is right ontop of any of the tiles.
 *
 *     isOnCeiling(rect, tiles, tilesLen)
 *       Returns a bool if the rect is right under of any of the tiles.
 *
 *     isOnWall(rect, tiles, tilesLen)
 *       Returns a bool if the rect is right next to any of the tiles.
 *
 */

#ifndef CPHYC_H
#define CPHYC_H

#ifdef T
#warning T already defined. Will overwrite.
#undef T
#endif /* T */
#ifdef __cplusplus
#define T(T) T
#define CPH_NULLPTR nullptr
namespace cph {
extern "C" {
#else
#define T(T) cph_##T
#define CPH_NULLPTR ((void*)0)
#endif /* __cplusplus */

typedef unsigned char T(Bool);

typedef struct T(Rect) {
	float x, y, w, h;
} T(Rect);

extern const T(Bool) T(TRUE);
extern const T(Bool) T(FALSE);

void T(moveAndCollide) (T(Rect) * rect, T(Rect) tiles[], unsigned inttilesLen, float velx, float vely);
T(Bool) T(isOnFloor) (T(Rect) rect, T(Rect) tiles[], unsigned inttilesLen);
T(Bool) T(isOnCeiling) (T(Rect) rect, T(Rect) tiles[], unsigned inttilesLen);
T(Bool) T(isOnWall) (T(Rect) rect, T(Rect) tiles[], unsigned inttilesLen);

/* Inline collision detection if supported. (Not a part of c89) */
#ifdef inline
#ifdef __cplusplus
#define INLINE inline
#else
#define INLINE static inline
#endif /* __cplusplus */
INLINE T(Bool) T(collideRect) (T(Rect) rect1, T(Rect) rect2) {
  return rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h;
}
#undef INLINE
#else
T(Bool) T(collideRect) (T(Rect) rect1, T(Rect) rect2);
#endif /* inline */

#ifdef CPHYC_IMPL

const T(Bool) T(TRUE) = 1;
const T(Bool) T(FALSE) = 0;

/* Work even if inlining isn't allowed. */
#ifndef inline
T(Bool) T(collideRect) (T(Rect) rect1, T(Rect) rect2) {
  return rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h;
}
#endif /* inline */

void T(moveAndCollide) (T(Rect) * rect, T(Rect) tiles[], unsigned int tilesLen, float velx, float vely) {
	T(Rect) r = *rect;
  unsigned int t;

	if (rect == CPH_NULLPTR) return;

	r.x += velx;
	for (t = 0; t < tilesLen; t++) {
		if ( T(collideRect) (r, tiles[t]) ) {
			if ( velx > 0 )
				r.x = tiles[t].x - r.w;
			else if (velx < 0)
				r.x = tiles[t].x + tiles[t].w;
		}
	}

	r.y += vely;
	for (t = 0; t < tilesLen; t++) {
		if ( T(collideRect) (r, tiles[t]) ) {
			if ( vely > 0 )
				r.y = tiles[t].y - r.h;
			else if (vely < 0)
				r.y = tiles[t].y + tiles[t].h;
		}
	}

	*rect = r;
}

T(Bool) T(isOnFloor) (T(Rect) rect, T(Rect) tiles[], unsigned int tilesLen) {
  unsigned int t;

	rect.y += rect.h;
	rect.h = 1;

	for (t = 0; t < tilesLen; t++) {
		if (T(collideRect) (rect, tiles[t]))
			return T(TRUE);
	}
	return T(FALSE);
}

T(Bool) T(isOnCeiling) (T(Rect) rect, T(Rect) tiles[], unsigned int tilesLen) {
  unsigned int t;

  --rect.y;
  rect.h = 1;

	for (t = 0; t < tilesLen; t++) {
		if (T(collideRect) (rect, tiles[t]))
			return T(TRUE);
	}
	return T(FALSE);
}

T(Bool) T(isOnWall) (T(Rect) rect, T(Rect) tiles[], unsigned int tilesLen) {
  unsigned int t;

	--rect.x;
	rect.w += 2;

	for (t = 0; t < tilesLen; t++) {
		if (T(collideRect) (rect, tiles[t]))
			return T(TRUE);
	}
	return T(FALSE);
}

#endif /* CPHYC_IMPL */

#ifdef __cplusplus
}}
#endif

#undef T
#undef CPH_NULLPTR

#endif /* CPHYC_H */

