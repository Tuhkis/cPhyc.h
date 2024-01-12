/*
 * File: cPhyc.h
 * Author: Nico Lindström
 * Copyright: (c) 2022-2023 Nico Lindström 
 * 
 * This is a header only library for AABB based physics
 * that is compatible with C and C++.
 *
 *
 * Documentation:
 *   Types:
 *     Rect
 *       A rectangle structure that stores its position and dimensions as 32 bit ints.
 *
 *   Macros:
 *     collideRect(rect1, rect2)
 *       Checks whetever two Rect's overlap.
 *
 *   Methods:
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

#pragma once
#ifndef CPHYC_H
#define CPHYC_H

#define collideRect(rect1, rect2) rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h

#define CPH_TRUE (1)
#define CPH_FALSE (0)

#ifdef __cplusplus
#define T(T) T
namespace cph {
extern "C" {
#else
#define T(T) cph_##T
#endif /* __cplusplus */

typedef unsigned char T(Bool);

typedef struct T(Rect) {
	float x, y, w, h;
} T(Rect);

void T(moveAndCollide) (T(Rect) * rect, T(Rect) tiles[], int tilesLen, float velx, float vely);	
T(Bool) T(isOnFloor) (T(Rect) rect, T(Rect) tiles[], int tilesLen);
T(Bool) T(isOnCeiling) (T(Rect) rect, T(Rect) tiles[], int tilesLen);
T(Bool) T(isOnWall) (T(Rect) rect, T(Rect) tiles[], int tilesLen);
#ifdef CPHYC_IMPL

void T(moveAndCollide) (T(Rect) * rect, T(Rect) tiles[], int tilesLen, float velx, float vely) {
	T(Rect) r = *rect;
  int t;

	r.x += velx;
	for (t = 0; t < tilesLen; t++) {
		if ( collideRect(r, tiles[t]) ) {
			if ( velx > 0 )
				r.x = tiles[t].x - r.w;
			else if (velx < 0)
				r.x = tiles[t].x + tiles[t].w;
		}
	}

	r.y += vely;
	for (t = 0; t < tilesLen; t++) {
		if ( collideRect(r, tiles[t]) ) {
			if ( vely > 0 )
				r.y = tiles[t].y - r.h;
			else if (vely < 0)
				r.y = tiles[t].y + tiles[t].h;
		}
	}

	*rect = r;
}

T(Bool) T(isOnFloor) (T(Rect) rect, T(Rect) tiles[], int tilesLen) {
	T(Rect) r = (T(Rect)) {rect.x, rect.y + rect.h, rect.w, 1};
  int t;
	for (t = 0; t < tilesLen; t++) {
		if (collideRect(r, tiles[t]))
			return CPH_TRUE;
	}
	return CPH_FALSE;
}

T(Bool) T(isOnCeiling) (T(Rect) rect, T(Rect) tiles[], int tilesLen) {
	T(Rect) r = (T(Rect)) {rect.x, rect.y - 1, rect.w, 1};
  int t;
	for (t = 0; t < tilesLen; t++) {
		if (collideRect(r, tiles[t]))
			return CPH_TRUE;
	}
	return CPH_FALSE;
}

T(Bool) T(isOnWall) (T(Rect) rect, T(Rect) tiles[], int tilesLen) {
	T(Rect) r = (T(Rect)) {rect.x - 1, rect.y, rect.w + 2, rect.h};
  int t;
	for (t = 0; t < tilesLen; t++) {
		if (collideRect(r, tiles[t]))
			return CPH_TRUE;
	}
	return CPH_FALSE;
}

#endif /* CPHYC_IMPL */

#ifdef __cplusplus
}}
#endif

#undef T

#endif /* CPHYC_H */

