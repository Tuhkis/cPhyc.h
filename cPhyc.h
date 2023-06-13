/*
 * File: cPhyc.h
 * Author: Nico Lindström
 * Copyright: (c) 2022 Nico Lindström 
 * 
 * This is a header only library for AABB based physics
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

#include <stdbool.h>

typedef struct {
	int x, y, w, h;
} Rect;

#define collideRect(rect1, rect2) rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h

void moveAndCollide(Rect* rect, Rect tiles[], int tilesLen, int velx, int vely);	
bool isOnFloor(Rect rect, Rect tiles[], int tilesLen);
bool isOnCeiling(Rect rect, Rect tiles[], int tilesLen);
bool isOnWall(Rect rect, Rect tiles[], int tilesLen);
#ifdef CPHYC_IMPL

void moveAndCollide(Rect* rect, Rect tiles[], int tilesLen, int velx, int vely) {
	Rect r = *rect;

	r.x += velx;
	for (int t = 0; t < tilesLen; t++) {
		if ( collideRect(r, tiles[t]) ) {
			if ( velx > 0 )
				r.x = tiles[t].x - r.w;
			else if (velx < 0)
				r.x = tiles[t].x + tiles[t].w;
		}
	}

	r.y += vely;
	for (int t = 0; t < tilesLen; t++) {
		if ( collideRect(r, tiles[t]) ) {
			if ( vely > 0 )
				r.y = tiles[t].y - r.h;
			else if (vely < 0)
				r.y = tiles[t].y + tiles[t].h;
		}
	}

	*rect = r;
}

bool isOnFloor(Rect rect, Rect tiles[], int tilesLen) {
	Rect r = (Rect) {rect.x, rect.y + rect.h, rect.w, 1};
	for (int t = 0; t < tilesLen; t++) {
		if (collideRect(r, tiles[t]))
			return true;
	}
	return false;
}

bool isOnCeiling(Rect rect, Rect tiles[], int tilesLen) {
	Rect r = (Rect) {rect.x, rect.y - 1, rect.w, 1};
	for (int t = 0; t < tilesLen; t++) {
		if (collideRect(r, tiles[t]))
			return true;
	}
	return false;
}

bool isOnWall(Rect rect, Rect tiles[], int tilesLen) {
	Rect r = (Rect) {rect.x - 1, rect.y, rect.w + 2, rect.h};
	for (int t = 0; t < tilesLen; t++) {
		if (collideRect(r, tiles[t]))
			return true;
	}
	return false;
}

#endif // CPHYC_IMPL
#endif // CPHYC_H

