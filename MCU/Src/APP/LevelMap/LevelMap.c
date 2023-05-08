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
		trace_printf("LevelMap_s32GetDepthAt(): \"wrong x and/or y in)\"");
		u8 contAfterErr = 0;
		__asm volatile ("bkpt 0");
		while(!contAfterErr);
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

void LevelMap_voidStoreToFlash(LevelMap_t* map)
{
	/*	unlock	*/
	if (FPEC_b8IsLocked())
		FPEC_voidUnlock();

	u8 base = map->flashSavingBasePage;

	/*	erase pages from base page to end of flash	*/
	FPEC_voidEnablePageEraseMode();
	for (u8 i = base; i < 64; i++)
		FPEC_voidErasePage(i);
	FPEC_voidDisablePageEraseMode();

	FPEC_voidEnableProgrammingMode();

	/*	store parameters of the map	*/
	FPEC_voidProgramHalfWord(FPEC_HALF_WORD_ADDRESS(base, 0), map->nX);
	FPEC_voidProgramHalfWord(FPEC_HALF_WORD_ADDRESS(base, 1), map->nY);

	FPEC_voidProgramWord(FPEC_HALF_WORD_ADDRESS(base, 2), map->sX);
	FPEC_voidProgramWord(FPEC_HALF_WORD_ADDRESS(base, 4), map->sY);

	FPEC_voidProgramWord(FPEC_HALF_WORD_ADDRESS(base, 6), map->eX);
	FPEC_voidProgramWord(FPEC_HALF_WORD_ADDRESS(base, 8), map->eY);



}

void LevelMap_voidRestoreFromFlash(LevelMap_t* map)
{
	if (FPEC_b8IsLocked())
		FPEC_voidUnlock();

	/*	N's	*/
	u8 base = map->flashSavingBasePage;
	map->nX = FPEC_u16ReadHalfWord(FPEC_HALF_WORD_ADDRESS(base, 0));
	map->nY = FPEC_u16ReadHalfWord(FPEC_HALF_WORD_ADDRESS(base, 1));

	/*	boundaries	*/
	map->sX = FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(base, 2));
	map->sY = FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(base, 4));
	map->eX = FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(base, 6));
	map->eY = FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(base, 8));

	/*	samples	*/
	for(u8 i = 0; i < map->nY; i++)
	{
		for(u8 j = 0; j < map->nX; j++)
		{
			u32 flashAddress = FPEC_WORD_ADDRESS(base + 1, i * map->nY + j);
			map->mapArr[i * map->nX + j] = FPEC_u32ReadWord(flashAddress);
		}
	}

	/*	init d's	*/
	LevelMap_voidInit(map);
}





















