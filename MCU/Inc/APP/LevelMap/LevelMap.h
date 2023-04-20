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

	s32 ds; // smaller of dX & dY

	/*
	 * number of the flash page at which program starts storing / restoring the
	 * 'LevelMap_t' object data.
	 */
	u8 flashSavingBasePage;
}LevelMap_t;

void LevelMap_voidInit(LevelMap_t* map);	// evaluated dX, dY and ds

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

void LevelMap_voidStoreToFlash(LevelMap_t* map);

/*
 * restores previously sampled working area. (useful at restoring system after
 * unexpected power reset, as it saves probing time)
 */
void LevelMap_voidRestoreFromFlash(LevelMap_t* map);
















#endif /* INCLUDE_APP_LEVELMAP_LEVELMAP_H_ */
