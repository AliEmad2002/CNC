/*
 * CNC_program.c
 *
 * Created: 7/20/2022 11:05:02 PM
 *
 * Copyright (c) 2022, Ali Emad
 * All rights reserved.
 *
 * This source code is licensed under the GPL-style license found in the
 * LICENSE file in the root directory of this source tree. 
 */


/*	LIB	*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <stdlib.h>
#include <stdio.h>
#include "My_Math.h"
#include <math.h>
#include "G_code_interface.h"
/*	MCAL	*/
#include "GPIO_interface.h"
#include "Delay_interface.h"
#include "STK_interface.h"
/*	HAL	*/
#include "Stepper_interface.h"

/*	SELF	*/
#include "CNC_private.h"
#include "CNC_config.h"
#include "CNC_interface.h"

static u64 ticksPerSecond;

void CNC_voidInit(CNC_t* CNC, DIO_PIN _autoLevelingProbePin, Stepper_t* stepperArr)
{
	/*	init _autoLevelingProbePin as pulled up input	*/
	CNC->autoLevelingProbePin = _autoLevelingProbePin % 16;
	CNC->autoLevelingProbePort = _autoLevelingProbePin / 16;
	DIO_voidSetPinMode(CNC->autoLevelingProbePort, CNC->autoLevelingProbePin, DIO_MODE_input);
	DIO_voidSetPinPull(CNC->autoLevelingProbePort, CNC->autoLevelingProbePin, DIO_PULL_up);
	
	/*	store stepperArr	*/
	CNC->stepperArr = stepperArr;
	
	/*	init arrays	*/
	/*	point will usually carry 3 items, but when AL is required, 5 items are stored	*/
	CNC->point = malloc(PIONT_ARR_MAX_LEN * sizeof(s32));
	CNC->mainParametersPtrArr = malloc(MAIN_PARAMETERS_ARR_LEN * sizeof(u32*));
	for (u8 i = 0; i < MAIN_PARAMETERS_ARR_LEN; i++)
		CNC->mainParametersPtrArr[i] = malloc(1 * sizeof(u32));
		
	/*	init parameters	*/
	*CNC->mainParametersPtrArr[CNC_relativePositioning] = 0;
	CNC->speedCurrent = 0;
	CNC->autoLevelingEnable = 0;
	
	ticksPerSecond = MSTK_u32GetTicksPerSecond();
}

void CNC_voidExecuteSoftwareSetPosition(CNC_t* CNC)
{
	for (u8 i=X; i<=Z; i++)
		CNC->stepperArr[i].currentPos = CNC->point[i];
}

void CNC_voidExecute(CNC_t* CNC, G_Code_Msg_t* msgPtr)
{
	if (msgPtr->codeClass == 'G')
	{
		switch (msgPtr->code)
		{
		case G_CODE_rapidMovement:
			G_Code_voidCopyPoint(CNC->point, msgPtr);
			CNC_voidExecuteMovement(CNC, CNC_MOVEMENTTYPE_rapid);
			break;

		case G_CODE_feedMovement:
			G_Code_voidCopyPoint(CNC->point, msgPtr);
			CNC->feedrate = msgPtr->paramNumArr[msgPtr->paramCount-1] * STEPS_PER_MM;
			CNC_voidExecuteMovement(CNC, CNC_MOVEMENTTYPE_feed);
			break;

		case G_CODE_autoLeveling:
			G_Code_voidCopyPointAL(CNC->point, msgPtr);
			CNC_voidExecuteAutoLeveling(CNC);
			break;

		case G_CODE_softwareSetPosition:
			G_Code_voidCopyPoint(CNC->point, msgPtr);
			CNC_voidExecuteSoftwareSetPosition(CNC);
			break;
		}
	}
	
	else if (msgPtr->codeClass == 'M')
	{
		switch (msgPtr->code)
		{
		case G_CODE_setMaxFeedrate:
			*CNC->mainParametersPtrArr[CNC_maxFeedrate] = msgPtr->paramNumArr[0] * STEPS_PER_MM;
			break;

		case G_CODE_setAcceleration:
			G_CODE_voidCopyAcceleration(CNC->mainParametersPtrArr, msgPtr);
			break;

		case G_CODE_enableAutoLeveling:
			CNC_voidExecuteRestoreSavedAutoLevelingData(CNC);
			break;
		}
	}
}

void CNC_voidExecuteMovement(CNC_t* CNC, CNC_MOVEMENTTYPE_t movementType)
{
	/*	prepare moving parameters	*/
	if (*CNC->mainParametersPtrArr[CNC_relativePositioning] == 0)
	{
		CNC->point[X] -= CNC->stepperArr[X].currentPos;
		CNC->point[Y] -= CNC->stepperArr[Y].currentPos;
	}
	
	u32 speed1 = CNC->speedCurrent;
	u32 speed2;
	u32 speedMax = *CNC->mainParametersPtrArr[CNC_maxFeedrate];
	u32 acceleration;
	
	if (movementType == CNC_MOVEMENTTYPE_rapid)
	{
		speed2 = 0;
		speedMax *= RAPID_SPEED_MAX_TO_FEED_SPEED_MAX;
		CNC->speedCurrent = 0;
		acceleration = *CNC->mainParametersPtrArr[CNC_accelerationRapid];
	}
	else	// if (movementType == CNC_MOVEMENTTYPE_feed)
	{
		speed2 = CNC->feedrate;
		if (speed2 > speedMax)
			speedMax = speed2;
			
		CNC->speedCurrent = speed2;
		acceleration = *CNC->mainParametersPtrArr[CNC_accelerationFeed];
	}
	
	/*	move	*/
	if (!CNC->autoLevelingEnable)
	{
		if (*CNC->mainParametersPtrArr[CNC_relativePositioning] == 0)
			CNC->point[Z] -= CNC->stepperArr[Z].currentPos;
		
		CNC_voidMove3Axis(
			CNC,
			CNC->point[X], CNC->point[Y], CNC->point[Z],
			speed1, speed2, speedMax, acceleration
			);
		return;
	}
	
	/*	if auto leveling is enabled	*/
	s32 zAbs = CNC->point[Z] + CNC_s32Depth(CNC, CNC->stepperArr[X].currentPos, CNC->stepperArr[Y].currentPos);
	s32 zSteps = zAbs - CNC->stepperArr[Z].currentPos;
	
	if (movementType == CNC_MOVEMENTTYPE_rapid)
	{
		/*
		 * no need to auto level along the movement.
		 * (to avoid high speed movement scattering)
		 */
		CNC_voidMove3Axis(
			CNC,
			CNC->point[X], CNC->point[Y], zSteps,
			speed1, speed2, speedMax, acceleration
			);
		return;
	}
	
	/*	make the z displacement first	*/
	CNC_voidMove3Axis(CNC, 0 ,0, zSteps, speed1, speed2, speedMax, acceleration);

	s32 dx, dy;
	
	s32 xMoved = 0;
	s32 yMoved = 0;
	
	s32* largestMovedPtr;
	
	if (labs(CNC->point[X]) > labs(CNC->point[Y]))
	{
		dx = CNC->autoLevelingDs * (s32)MATH_s16FindSignOf(CNC->point[X]) / AL_GRID_TRIMMER;
		dy = (s32)((s64)dx * (s64)CNC->point[Y] / (s64)CNC->point[X]);
		
		/*
		 * if yDisplacement was very very small relative to dx, dy would be
		 * calculated zero, resulting in an infinite loop in the following,
		 * so correct it and make yDisplacement.
		 */
		if (dy == 0		&&		CNC->point[Y] != 0)
			dy = CNC->point[Y];
			
		largestMovedPtr = &xMoved;
	}
	else
	{
		dy = CNC->autoLevelingDs * (s32)MATH_s16FindSignOf(CNC->point[Y]) / AL_GRID_TRIMMER;
		dx = (s32)((s64)dy * (s64)CNC->point[X] / (s64)CNC->point[Y]);
		
		if (dx == 0		&&		CNC->point[X] != 0)
			dx = CNC->point[X];
		
		largestMovedPtr = &yMoved;
	}
	
	u32 speed2Trim = speed1;
	u32 speedMaxTrim = (speed2Trim > CNC->speedCurrent) ? speed2Trim : CNC->speedCurrent;
	
	while (labs(xMoved) < labs(CNC->point[X])	||	labs(yMoved) < labs(CNC->point[Y]))
	{
		if (labs(xMoved + dx) >= labs(CNC->point[X]))
			dx = CNC->point[X] - xMoved;
			
		if (labs(yMoved + dy) >= labs(CNC->point[Y]))
			dy = CNC->point[Y] - yMoved;
		
		// make the wanted z-axis material-bit distance:
		zAbs = CNC->point[Z] + CNC_s32Depth(CNC, CNC->stepperArr[X].currentPos + dx, CNC->stepperArr[Y].currentPos + dy);
		zSteps = zAbs - CNC->stepperArr[Z].currentPos;
		
		CNC_voidMove3Axis(
			CNC,
			dx, dy, zSteps,
			CNC->speedCurrent, speed2Trim,
			speedMaxTrim, acceleration
			);
		
		xMoved += dx;
		yMoved += dy;
		
		// periodic change speed:
		if (labs(*largestMovedPtr) % SPEED_CHANGE_DELTA == 0)
		{
			CNC->speedCurrent = speed2Trim;
			
			speed2Trim = CNC_d64GetEstematedSpeed(
				speed1, speed2, speedMax, acceleration, CNC->point[X], CNC->point[Y], 0,
				sqrt((s64)xMoved * (s64)xMoved + (s64)yMoved * (s64)yMoved)
				);
				
			speedMaxTrim = (speed2Trim > CNC->speedCurrent) ? speed2Trim : CNC->speedCurrent;
		}
	}
}

void CNC_voidExecuteAutoLeveling(CNC_t* CNC)
{
	CNC->autoLevelingEnable = true;
	/* take (N*N) points, where N=V+3	*/
	CNC->autoLevelingGridxN = (u8)CNC->point[4] + 3;
	CNC->autoLevelingGridyN = (u8)CNC->point[5] + 3;
	CNC->autoLevelingStartX = CNC->point[0];
	CNC->autoLevelingStartY = CNC->point[2];
	CNC->autoLevelingEndX = CNC->point[1];
	CNC->autoLevelingEndY = CNC->point[3];
	CNC->autoLevelingDy = (CNC->autoLevelingEndY - CNC->autoLevelingStartY) / (s32)(CNC->autoLevelingGridyN - 1);
	CNC->autoLevelingDx = (CNC->autoLevelingEndX - CNC->autoLevelingStartX) / (s32)(CNC->autoLevelingGridxN - 1);
	CNC->autoLevelingDs = (CNC->autoLevelingDx < CNC->autoLevelingEndY) ? CNC->autoLevelingDx : CNC->autoLevelingDy;

		//for (u8 i=0; i<15; i++)
			//for (u8 j=0; j<15; j++)
				//CNC->autoLevelingMap[i][j] = 0;
		//return;
	
	///*	EEPROM store	*/
	///*	EEPROM[0] = N	*/
	//EEPROM_voidWriteByte(0, CNC->autoLevelingGridN);
	///*	EEPROM[1:4] = autoLevelingStartX	*/
	//EEPROM_voidWrite4Bytes(1, (u32)CNC->autoLevelingStartX);
	///*	EEPROM[5:8] = autoLevelingStartY	*/
	//EEPROM_voidWrite4Bytes(5, (u32)CNC->autoLevelingStartY);
	///*	EEPROM[9:12] = autoLevelingEndX		*/
	//EEPROM_voidWrite4Bytes(9, (u32)CNC->autoLevelingEndX);
	///*	EEPROM[13:16] = autoLevelingEndY	*/
	//EEPROM_voidWrite4Bytes(13, (u32)CNC->autoLevelingEndY);
	
	u8 i = 0;
	u8 j = 0;
	CNC->autoLevelingMap = (s32**)malloc(CNC->autoLevelingGridyN * sizeof(s32*));
	for (s32 y=CNC->autoLevelingStartY; y<=CNC->autoLevelingEndY; y+=CNC->autoLevelingDy)
	{
		CNC->autoLevelingMap[i] = (s32*)malloc(CNC->autoLevelingGridxN * sizeof(s32));
		s32 x;
		s32 dx;
		u8 jFinal;
		// at odd lines, take samples from the end back to beginning:
		if (i % 2)
		{
			 x = CNC->autoLevelingEndX;
			 dx = -CNC->autoLevelingDx;
			 jFinal = 0;
			 j = CNC->autoLevelingGridxN - 1;
		}
		// while even lines are normally sampled from 0 to N - 1:
		else
		{
			x = CNC->autoLevelingStartX;
			dx = CNC->autoLevelingDx;
			jFinal = CNC->autoLevelingGridxN - 1;
			j = 0;
		}
		for (;;)
		{
			/*	go to that point of (x, y)	*/
			// tool up:
			CNC_voidMove3Axis(
				CNC,
				0, 0, AUTO_LEVELING_UP,
				0, 0,
				RAPID_SPEED_MAX_TO_FEED_SPEED_MAX * *CNC->mainParametersPtrArr[CNC_maxFeedrate], *CNC->mainParametersPtrArr[CNC_accelerationRapid]
				);
			// move to (x, y):
			CNC_voidMove3Axis(
				CNC,
				x - CNC->stepperArr[X].currentPos, y - CNC->stepperArr[Y].currentPos, 0,
				0, 0,
				RAPID_SPEED_MAX_TO_FEED_SPEED_MAX * *CNC->mainParametersPtrArr[CNC_maxFeedrate], *CNC->mainParametersPtrArr[CNC_accelerationRapid]
				);
			
			// probe:
			CNC_voidProbe(CNC);
			
			///*	save current z position (in (u32)steps) to EEPROM		*/
			///*								 ^~~~~ IMPORTANT! NOTICE!	*/
			//u16 eepromAddress = 17 + 4 * ((u16)j + (u16)(i * CNC->autoLevelingGridN));
			//EEPROM_voidWrite4Bytes(eepromAddress, (u32)CNC->stepperArr[2].currentPos);
			
			/*	save current z position to RAM	*/
			CNC->autoLevelingMap[i][j] = (s32)(CNC->stepperArr[Z].currentPos);
			
			if (j == jFinal)
				break;
			
			if (i % 2)
				j--;
			else
				j++;
			
			x += dx;
		}
		i++;
	}
	
	/*	go home	*/
	CNC_voidMove3Axis(
		CNC,
		0, 0, AUTO_LEVELING_UP*10 - CNC->stepperArr[Z].currentPos,
		0, 0,
		RAPID_SPEED_MAX_TO_FEED_SPEED_MAX * *CNC->mainParametersPtrArr[CNC_maxFeedrate], *CNC->mainParametersPtrArr[CNC_accelerationRapid]
		);
	
	CNC_voidMove3Axis(
		CNC,
		-CNC->stepperArr[X].currentPos, -CNC->stepperArr[Y].currentPos,
		AUTO_LEVELING_UP_MAX - CNC->stepperArr[Z].currentPos,
		0, 0,
		RAPID_SPEED_MAX_TO_FEED_SPEED_MAX * *CNC->mainParametersPtrArr[CNC_maxFeedrate], *CNC->mainParametersPtrArr[CNC_accelerationRapid]
		);
	
	CNC_voidMove3Axis(
		CNC,
		0, 0, -CNC->stepperArr[Z].currentPos,
		0, 0,
		RAPID_SPEED_MAX_TO_FEED_SPEED_MAX * *CNC->mainParametersPtrArr[CNC_maxFeedrate], *CNC->mainParametersPtrArr[CNC_accelerationRapid]
		);
}

void CNC_voidExecuteRestoreSavedAutoLevelingData(CNC_t* CNC)
{
	///*	enable auto leveling	*/
	//CNC->autoLevelingEnable = 1;
	//
	///*	read EEPROM	*/
	///*	EEPROM[0] = N	*/
	//CNC->autoLevelingGridN = EEPROM_u8ReadByte(0);
	///*	check that there's data	*/
	//if (CNC->autoLevelingGridN > 10)
	//{
		///*	wrong stored data	*/
		//while(1);
	//}
	///*	EEPROM[1:4] = autoLevelingStartX	*/
	//CNC->autoLevelingStartX = (s32)EEPROM_u32Read4Bytes(1);
	///*	EEPROM[5:8] = autoLevelingStartY	*/
	//CNC->autoLevelingStartY = (s32)EEPROM_u32Read4Bytes(5);
	///*	EEPROM[9:12] = autoLevelingEndX		*/
	//CNC->autoLevelingEndX = (s32)EEPROM_u32Read4Bytes(9);
	///*	EEPROM[13:16] = autoLevelingEndY	*/
	//CNC->autoLevelingEndY = (s32)EEPROM_u32Read4Bytes(13);
	//
	///*	There should be N*N numbers of s32 type stored starting from EEPROM[17], store them in RAM for speed of access:	*/
	////CNC->autoLevelingMap = malloc(CNC->autoLevelingGridN * sizeof(s32*));
	//for (u8 i=0; i<CNC->autoLevelingGridN; i++)
	//{
		////CNC->autoLevelingMap[i] = malloc(CNC->autoLevelingGridN * sizeof(s32));
		//for (u8 j=0; j<CNC->autoLevelingGridN; j++)
		//{
			//u16 eepromAddress = 17 + 4 * ((u16)j + (u16)(i * CNC->autoLevelingGridN));
			//CNC->autoLevelingMap[i][j] = (s32)EEPROM_u32Read4Bytes(eepromAddress);
		//}
	//}
	//
	///*	dy, dx and ds	*/
	//CNC->autoLevelingDy = (CNC->autoLevelingEndY - CNC->autoLevelingStartY) / (s32)(CNC->autoLevelingGridN - 1);
	//CNC->autoLevelingDx = (CNC->autoLevelingEndX - CNC->autoLevelingStartX) / (s32)(CNC->autoLevelingGridN - 1);
	//CNC->autoLevelingDs = (CNC->autoLevelingDx < CNC->autoLevelingEndY) ? CNC->autoLevelingDx : CNC->autoLevelingDy;
}

s32 CNC_s32Depth(CNC_t* CNC, s32 x, s32 y)
{
	/*	Check that x and y are in the scanned grid	*/
	if (
		CNC->autoLevelingStartY > y	||	y > CNC->autoLevelingEndY	||
		CNC->autoLevelingStartX > x	||	x > CNC->autoLevelingEndX
		)
	{
		/*	wrong x and/or y	*/
		return 0;
	}
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	finding iP, jP	*/
	u8 iP = (u8)((y - CNC->autoLevelingStartY) / CNC->autoLevelingDy);
	u8 jP = (u8)((x - CNC->autoLevelingStartX) / CNC->autoLevelingDx);
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	finding four surrounding points	*/
	s64 xL = CNC->autoLevelingStartX + ((s32)jP) * CNC->autoLevelingDx;
	s64 yT = CNC->autoLevelingStartY + ((s32)iP) * CNC->autoLevelingDy;
	
	s64 dTL = CNC->autoLevelingMap[iP][jP];
	s64 dTR = CNC->autoLevelingMap[iP][jP+1];
	s64 dBL = CNC->autoLevelingMap[iP+1][jP];
	s64 dBR = CNC->autoLevelingMap[iP+1][jP+1];
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	Bilinear interpolation	*/
	s64 d =
		dTL * (xL + CNC->autoLevelingDx - x) * (yT + CNC->autoLevelingDy - y) +
		dBL * (x - xL) * (yT + CNC->autoLevelingDy - y) +
		dTR * (xL + CNC->autoLevelingDx - x) * (y - yT) +
		dBR * (x - xL) * (y - yT);
	d /= (((s64)(CNC->autoLevelingDx)) * ((s64)(CNC->autoLevelingDy)));
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	return (s32)d;
}

u32 CNC_d64GetEstematedSpeed(
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement, u32 dDone
	)
{
	u32 displacementMagnitude = sqrt(
	(s64)xDisplacement * (s64)xDisplacement +
	(s64)yDisplacement * (s64)yDisplacement +
	(s64)zDisplacement * (s64)zDisplacement
	);
	
	u64 speed1Squared = (u64)speed1 * (u64)speed1;
	u64 speed2Squared = (u64)speed2 * (u64)speed2;
	u64 speedMaxSquared = (u64)speedMax * (u64)speedMax;
	u32 accelerationDoubled = 2 * acceleration;
	
	s32 d1 = speedMaxSquared / accelerationDoubled	- speed1Squared / accelerationDoubled;
	s32 d3 = speedMaxSquared / accelerationDoubled - speed2Squared / accelerationDoubled;
	
	s32 d2 = displacementMagnitude - (d1 + d3);
	if (d2 < 0)
	{
		// d2 value is to be divided into two relative parts, each added to d1 or d3 as needed,
		// to shorten d1, d2.
		//d64 sumAccelerationAndDeceleration = acceleration + deceleration;
		s32 d2Half = d2 / 2;
		
		d1 = d1 + d2Half; // * acceleration / sumAccelerationAndDeceleration;
		
		d3 = d3 + d2Half; // * deceleration / sumAccelerationAndDeceleration;
		
		if (d1 < 0)
			d1 = 0;
		
		if (d3 < 0)
			d3 = 0;
		
		speedMax = sqrt((u64)accelerationDoubled * (u64)d1 + speed1Squared);
		speedMaxSquared = (u64)speedMax * (u64)speedMax;
		
		// this d2 can't ever be negative, as this is compensated in the windows program.
		//d2 = displacementMagnitude - (d1 + d3);	// it should be zero.
		d2 = 0;
	}
	
	if (dDone < d1)	// still accelerating:
		return sqrt(speed1Squared + (u64)accelerationDoubled * (u64)dDone);
		
	else if (dDone < d1+d2)	// reached speedMax and running by it:
		return speedMax;
		
	else //if (dDone < d1+d2+d3)	// decelerating:
		return sqrt(speedMaxSquared - (u64)accelerationDoubled * (u64)dDone);
}

void CNC_voidMove3Axis(
	CNC_t* CNC,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement,
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration
	)
{
	Stepper_t* stepperArr = CNC->stepperArr;
	
	s32 displacementsAbs[3] = {xDisplacement, yDisplacement, zDisplacement};	// to be absoluted later...
	
	/*
	 * storing current position to compensate error at the end of movement.
	 * (absolute of error is less than 4 steps)
	 */
	s32 posStart[3] = {stepperArr[0].currentPos, stepperArr[1].currentPos, stepperArr[2].currentPos};
	
	/*	magnitude of distance to be moved	*/
	s32 displacementMagnitude = sqrt(
		(s64)xDisplacement * (s64)xDisplacement +
		(s64)yDisplacement * (s64)yDisplacement +
		(s64)zDisplacement * (s64)zDisplacement
		);
	
	/*	storing heavy calculations	*/
	u64 speed1Squared = (u64)speed1 * (u64)speed1;
	u64 speed2Squared = (u64)speed2 * (u64)speed2;
	u64 speedMaxSquared = (u64)speedMax * (u64)speedMax;
	u32 accelerationDoubled = 2 * acceleration;
	
	/*	calculating distances of different types of acceleration	*/
	s32 d1 = speedMaxSquared / accelerationDoubled	- speed1Squared / accelerationDoubled;
	s32 d3 = speedMaxSquared / accelerationDoubled - speed2Squared / accelerationDoubled;
	s32 d2 = displacementMagnitude - (d1 + d3);
	
	/*	if maximum value of "speed" in this exact movement is not going to reach "speedMax"	*/
	if (d2 < 0)
	{
		/*
		 * d2 value is to be divided into two relative parts, each added to d1 or d3 as needed,
		 * to shorten d1, d2.
		 */
		s32 d2Half = d2 / 2;
		
		d1 = d1 + d2Half;
		d3 = d3 + d2Half;
		
		/*	maximum speed in this movement	*/
		speedMax = sqrt((u64)accelerationDoubled * (u64)d1 + speed1Squared);
		speedMaxSquared = (u64)speedMax * (u64)speedMax;
		
		/*
		 * this d2 can't ever be any thing other than zero, as this is compensated in the windows program.
		 * same for d1 and d3, they can't ever be negative. but if any other commands that do not compensate
		 * these calculations, it is handled by zeroing.
		 */
		d2 = 0;
		
		if (d1 < 0)
			d1 = 0;
		
		if (d3 < 0)
			d3 = 0;
	}
	
	volatile u32 speed = (speed1 < SPEED_MIN) ? SPEED_MIN : speed1;
	
	volatile u64 timeCurrent;
	
	Stepper_dir dir[3];
	for (u8 i = 0; i < 3; i++)
	{
		dir[i] = (displacementsAbs[i] >= 0) ? Stepper_dir_forward : Stepper_dir_backward;
		displacementsAbs[i] = labs(displacementsAbs[i]);
	}
	
	u32 dDoneMost = 0;
	u32 dTotalMost;
	u32 dDone[2] = {0, 0};
	u32 dTotal[2];
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	sort axis by most displacement	*/
	static u8 axisSorted[3] = {0, 1, 2};
	
	for (u8 i=0; i<2; i++)
	{
		for (u8 j=i+1; j<3; j++)
		{
			if (displacementsAbs[axisSorted[j]] > displacementsAbs[axisSorted[i]])
			{
				u8 temp = axisSorted[j];
				axisSorted[j] = axisSorted[i];
				axisSorted[i] = temp;
			}
		}
	}
	
	s32 mostDisplacementAbs = displacementsAbs[axisSorted[0]];
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	u64 deltaTMost = (ticksPerSecond * (u64)displacementMagnitude) / (u64)displacementsAbs[axisSorted[0]] / (u64)speed;
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	steps that most displacement magnitude axis should make before other axis make single one	*/
	u32 stepsOfMostToStep[2];

	if (displacementsAbs[axisSorted[1]] == 0)
		stepsOfMostToStep[0] = displacementsAbs[axisSorted[0]] + 1;	// so it never steps.
	else
		stepsOfMostToStep[0] = displacementsAbs[axisSorted[0]] / displacementsAbs[axisSorted[1]];

	if (displacementsAbs[axisSorted[2]] == 0)
		stepsOfMostToStep[1] = displacementsAbs[axisSorted[0]] + 1;	// so it never steps.
	else
		stepsOfMostToStep[1] = displacementsAbs[axisSorted[0]] / displacementsAbs[axisSorted[2]];
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	starting from speed1, accelerate to speedMax	*/
	/*	stepper of most displacement magnitude is the only one to be timed,	*/
	/*	while the other two don't need to, as they depend on the first	*/	
	dTotalMost = ((u64)d1 * (u64)displacementsAbs[axisSorted[0]]) / displacementMagnitude;
	dTotal[0] = ((u64)d1 * (u64)displacementsAbs[axisSorted[1]]) / displacementMagnitude;
	dTotal[1] = ((u64)d1 * (u64)displacementsAbs[axisSorted[2]]) / displacementMagnitude;
		
	while(dDoneMost < dTotalMost	&&		dDoneMost < mostDisplacementAbs)
	{
		timeCurrent = MSTK_u64GetElapsedTicks();
		if (timeCurrent - stepperArr[axisSorted[0]].lastTimeStamp > deltaTMost)
		{
			Stepper_voidStep(stepperArr + axisSorted[0], dir[axisSorted[0]], timeCurrent);
			dDoneMost++;
			
			if (dDoneMost % stepsOfMostToStep[0] == 0)
			{
				if (dDone[0] < dTotal[0])
				{
					/* time to step stepper axisSorted[1]	*/
					Stepper_voidStep(stepperArr + axisSorted[1], dir[axisSorted[1]], timeCurrent);
					dDone[0]++;
				}
			}
				
			if (dDoneMost % stepsOfMostToStep[1] == 0)
			{
				if (dDone[1] < dTotal[1])
				{
					/* time to step stepper axisSorted[2]	*/
					Stepper_voidStep(stepperArr + axisSorted[2], dir[axisSorted[2]], timeCurrent);
					dDone[1]++;
				}
			}
		}
		
		/*	change speed every certain configured interval	*/
		if (!(dDoneMost % SPEED_CHANGE_DELTA))
		{
			speed = sqrtf(speed1Squared + ((u64)accelerationDoubled * (u64)dDoneMost * (u64)displacementMagnitude) / displacementsAbs[axisSorted[0]]);
			if (speed < SPEED_MIN)
				speed = SPEED_MIN;
			deltaTMost = (ticksPerSecond * (u64)displacementMagnitude) / (u64)displacementsAbs[axisSorted[0]] / (u64)speed;
		}
	}
	
	/* changing speed in case an interval change did not happen in d1	*/
	speed = sqrtf(speed1Squared + ((u64)accelerationDoubled * (u64)dDoneMost * (u64)displacementMagnitude) / displacementsAbs[axisSorted[0]]);
	if (speed < SPEED_MIN)
		speed = SPEED_MIN;
	deltaTMost = (ticksPerSecond * (u64)displacementMagnitude) / (u64)displacementsAbs[axisSorted[0]] / (u64)speed;
	
	mostDisplacementAbs -= dDoneMost;
	dDoneMost = 0;
	dDone[0] = 0;
	dDone[1] = 0;
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	stay on speedMax for d2	*/
	dTotalMost = ((u64)d2 * (u64)displacementsAbs[axisSorted[0]]) / displacementMagnitude;
	dTotal[0] = ((u64)d2 * (u64)displacementsAbs[axisSorted[1]]) / displacementMagnitude;
	dTotal[1] = ((u64)d2 * (u64)displacementsAbs[axisSorted[2]]) / displacementMagnitude;
	
	while(dDoneMost < dTotalMost		&&		dDoneMost < mostDisplacementAbs)
	{
		timeCurrent = MSTK_u64GetElapsedTicks();
		if (timeCurrent - stepperArr[axisSorted[0]].lastTimeStamp > deltaTMost)
		{
			Stepper_voidStep(stepperArr + axisSorted[0], dir[axisSorted[0]], timeCurrent);
			dDoneMost++;
			
			if (dDoneMost % stepsOfMostToStep[0] == 0)
			{
				if (dDone[0] < dTotal[0])
				{
					/* time to step stepper axisSorted[1]	*/
					Stepper_voidStep(stepperArr + axisSorted[1], dir[axisSorted[1]], timeCurrent);
					dDone[0]++;
				}
			}
			
			if (dDoneMost % stepsOfMostToStep[1] == 0)
			{
				if (dDone[1] < dTotal[1])
				{
					/* time to step stepper axisSorted[2]	*/
					Stepper_voidStep(stepperArr + axisSorted[2], dir[axisSorted[2]], timeCurrent);
					dDone[1]++;
				}
			}
		}
	}
	mostDisplacementAbs -= dDoneMost;
	
	dDoneMost = 0;
	dDone[0] = 0;
	dDone[1] = 0;
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	starting from speedMax, decelerate to speed2	*/
	
	dTotalMost = ((u64)d3 * (u64)displacementsAbs[axisSorted[0]]) / displacementMagnitude;
	dTotal[0] = ((u64)d3 * (u64)displacementsAbs[axisSorted[1]]) / displacementMagnitude;
	dTotal[1] = ((u64)d3 * (u64)displacementsAbs[axisSorted[2]]) / displacementMagnitude;
	
	while(dDoneMost < dTotalMost	&&		dDoneMost < mostDisplacementAbs)
	{
		timeCurrent = MSTK_u64GetElapsedTicks();
		if (timeCurrent - stepperArr[axisSorted[0]].lastTimeStamp > deltaTMost)
		{
			Stepper_voidStep(stepperArr + axisSorted[0], dir[axisSorted[0]], timeCurrent);
			dDoneMost++;
			
			if (dDoneMost % stepsOfMostToStep[0] == 0)
			{
				if (dDone[0] < dTotal[0])
				{
					/* time to step stepper axisSorted[1]	*/
					Stepper_voidStep(stepperArr + axisSorted[1], dir[axisSorted[1]], timeCurrent);
					dDone[0]++;
				}
			}
			
			if (dDoneMost % stepsOfMostToStep[1] == 0)
			{
				if (dDone[1] < dTotal[1])
				{
					/* time to step stepper axisSorted[2]	*/
					Stepper_voidStep(stepperArr + axisSorted[2], dir[axisSorted[2]], timeCurrent);
					dDone[1]++;
				}
			}
		}
		
		// if 1mm was made:
		if (!(dDoneMost % SPEED_CHANGE_DELTA))
		{
			speed = sqrtf(speedMaxSquared - ((u64)accelerationDoubled * (u64)dDoneMost * (u64)displacementMagnitude) / displacementsAbs[axisSorted[0]]);
			if (speed < SPEED_MIN)
				speed = SPEED_MIN;
			deltaTMost = (ticksPerSecond * (u64)displacementMagnitude) / (u64)displacementsAbs[axisSorted[0]] / (u64)speed;
		}
	}
	mostDisplacementAbs -= dDoneMost;
	dDoneMost = 0;
	dDone[0] = 0;
	dDone[1] = 0;
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	/*	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	*/
	
	/*	compensate precision error	*/
	s32 error[3] = {
		xDisplacement - stepperArr[0].currentPos + posStart[0],
		yDisplacement - stepperArr[1].currentPos + posStart[1],
		zDisplacement - stepperArr[2].currentPos + posStart[2]
	};
	
	for (u8 i=0; i<3; i++)
	{
		dir[i] = (error[i] >= 0.0) ? Stepper_dir_forward : Stepper_dir_backward;
		error[i] = labs(error[i]);
	}
	
	u32 dDone3[3] = {0, 0, 0};
	
	while(dDone3[0] < error[0]	||	dDone3[1] < error[1]	||	dDone3[2] < error[2])
	{
		timeCurrent = MSTK_u64GetElapsedTicks();
		for (u8 i = 0; i < 3; i++)
		{
			if (timeCurrent - stepperArr[i].lastTimeStamp > deltaTMost)
			{
				if (dDone3[i] < error[i])
				{
					Stepper_voidStep(stepperArr + i, dir[i], timeCurrent);
					dDone3[i]++;
				}
			}
		}
	}
}

void CNC_voidProbe(CNC_t* CNC)
{
	/*	start lowering the head until contact occurs (first touch)	*/
	/*	assuming pin is pulled up, and contact is when it contacts GND	*/
	u64 timeCurrent = MSTK_u64GetElapsedTicks();

	u32 steps = 0;
	while(DIO_b8ReadPinDigital(CNC->autoLevelingProbePort, CNC->autoLevelingProbePin))
	{
		if (timeCurrent - CNC->stepperArr[2].lastTimeStamp >= AL_SLOW_SPEED_TICKS_PER_STEP)
		{
			Stepper_voidStep(&CNC->stepperArr[2], Stepper_dir_backward, timeCurrent);
			steps++;

			if (steps > MAX_PROBE_STEPS)
			{
				while(1);
			}
		}
		
		timeCurrent = MSTK_u64GetElapsedTicks();
	}
}
