/*
 * LevelMap.h
 *
 *  Created on: Apr 20, 2023
 *      Author: Ali Emad
 */

#ifndef INCLUDE_APP_LEVELMAP_LEVELMAP_H_
#define INCLUDE_APP_LEVELMAP_LEVELMAP_H_

typedef struct{
	s32* mapArr; // statically user allocated. Expresses depth in steps.

	u8 nX;
	u8 nY;

	s32 sX;
	s32 sY;

	s32 eX;
	s32 eY;

	s32 dX;
	s32 dY;

	SD_Stream_t stream;
}LevelMap_t;

void LevelMap_voidInit(LevelMap_t* map);	// evaluates dX, dY

/*
 * Sets depth of a point on the map, given indexes of its containing cell in
 * the map array.
 * displacement unit is 'step'.
 */
void LevelMap_voidSetDepthAt(LevelMap_t* map, u8 cellY, u8 cellX, s32 depth);

/*
 * applies bilinear interpolation on the depths of the four bounding points of
 * the point (x, y), to estimate its own depth.
 * displacement unit is 'step'.
 */
s32 LevelMap_s32GetDepthAt(LevelMap_t* map, s32 x, s32 y);

/*
 * Saves the map array currently available in RAM to the file "MAP.RFS" on SD-card
 */
void LevelMap_voidSaveOnSDCard(LevelMap_t* map);

/*
 * Loads data from "MAP.RFS" on SD-card to RAM.
 */
void LevelMap_voidRestoreFromSDCard(LevelMap_t* map);
















#endif /* INCLUDE_APP_LEVELMAP_LEVELMAP_H_ */
