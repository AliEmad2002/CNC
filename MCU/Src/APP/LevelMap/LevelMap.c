/*
 * LevelMap.c
 *
 *  Created on: Apr 20, 2023
 *      Author: Ali Emad
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include <diag/trace.h>

/*	MCAL	*/
#include "FPEC_interface.h"

/*	HAL	*/
#include "SDC_interface.h"

/*	SELF	*/
#include "LevelMap.h"


void LevelMap_voidInit(LevelMap_t* map)		// evaluates dX, dY
{
	map->dY = (map->eY - map->sY) / (s32)(map->nY - 1);
	map->dX = (map->eX - map->sX) / (s32)(map->nX - 1);
}

void LevelMap_voidSetDepthAt(LevelMap_t* map, u8 cellY, u8 cellX, s32 depth)
{
	map->mapArr[cellY * map->nX + cellX] = depth;
}

s32 LevelMap_s32GetDepthAt(LevelMap_t* map, s32 x, s32 y)
{
	/*	Check that x and y are in the scanned grid	*/
	if (map->sY > y	|| y > map->eY || map->sX > x || x > map->eX)
	{
		/*	wrong x and/or y	*/
//		trace_printf("LevelMap_s32GetDepthAt(): \"wrong x and/or y in)\"");
//		volatile u8 contAfterErr = 0;
//		__asm volatile ("bkpt 0");
//		while(!contAfterErr);
		return 0;
	}

	/*	finding iP, jP	*/
	u8 iP = (u8)((y - map->sY) / map->dY);
	u8 jP = (u8)((x - map->sX) / map->dX);

	/*	finding four surrounding points	*/
	s64 xL = map->sX + ((s32)jP) * map->dX;
	s64 yT = map->sY + ((s32)iP) * map->dY;

	s64 dTL = map->mapArr[iP * map->nX + jP];				//	[iP][jP]
	s64 dTR = map->mapArr[iP * map->nX + jP+1];				//	[iP][jP+1]
	s64 dBL = map->mapArr[(iP+1) * map->nX + jP];			//	[iP+1][jP]
	s64 dBR = map->mapArr[(iP+1) * map->nX + jP+1];			//	[iP+1][jP+1]

	/*	Bilinear interpolation	*/
	volatile s64 d =
		dTL * (xL + map->dX - x) * (yT + map->dY - y) +
		dBL * (x - xL) * (yT + map->dY - y) +
		dTR * (xL + map->dX - x) * (y - yT) +
		dBR * (x - xL) * (y - yT);
	d /= (((s64)(map->dX)) * ((s64)(map->dY)));

	return (s32)d;
}

void LevelMap_voidSaveOnSDCard(LevelMap_t* map)
{
	/*	store parameters of the map	*/
	SDC_voidKeepTryingWriteStream(&(map->stream), 0, (u8*)&(map->nX), 1);
	SDC_voidKeepTryingWriteStream(&(map->stream), 1, (u8*)&(map->nY), 1);

	SDC_voidKeepTryingWriteStream(&(map->stream), 2, (u8*)&(map->sX), 4);
	SDC_voidKeepTryingWriteStream(&(map->stream), 6, (u8*)&(map->sY), 4);

	SDC_voidKeepTryingWriteStream(&(map->stream), 10, (u8*)&(map->eX), 4);
	SDC_voidKeepTryingWriteStream(&(map->stream), 14, (u8*)&(map->eY), 4);

	/*	store the map itself	*/
	u32 n = map->nX * map->nY;
	for (u32 i = 0; i < n; i++)
	{
		SDC_voidKeepTryingWriteStream(&(map->stream), 18 + i * 4, (u8*)&(map->mapArr[i]), 4);
	}

	SDC_voidKeepTryingSaveStream(&(map->stream));
}

void LevelMap_voidRestoreFromSDCard(LevelMap_t* map)
{
	/*	restore parameters of the map	*/
	SDC_voidKeepTryingReadStream(&(map->stream), 0, &(map->nX), 1);
	SDC_voidKeepTryingReadStream(&(map->stream), 1, &(map->nY), 1);

	SDC_voidKeepTryingReadStream(&(map->stream), 2, (u8*)&(map->sX), 4);
	SDC_voidKeepTryingReadStream(&(map->stream), 6, (u8*)&(map->sY), 4);

	SDC_voidKeepTryingReadStream(&(map->stream), 10, (u8*)&(map->eX), 4);
	SDC_voidKeepTryingReadStream(&(map->stream), 14, (u8*)&(map->eY), 4);

	/*	restore the map itself	*/
	u32 n = map->nX * map->nY;
	for (u32 i = 0; i < n; i++)
	{
		SDC_voidKeepTryingReadStream(&(map->stream), 18 + i * 4, (u8*)&(map->mapArr[i]), 4);
	}

	/*	init d's	*/
	LevelMap_voidInit(map);
}





















