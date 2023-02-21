/*
 * CNC_program.c
 *
 * Created: 	07/20/2022
 * Last Mod:	23/10/2022
 *  Author: Ali Emad Ali
 */ 


/*	LIB	*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "My_Math.h"
#include "G_code_interface.h"
#include "Delay_interface.h"
#include "Error_Handler_interface.h"

/*	MCAL	*/
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "FPEC_interface.h"

/*	HAL	*/
#include "Stepper_interface.h"

/*	SELF	*/
#include "CNC_private.h"
#include "CNC_config.h"
#include "CNC_interface.h"

static u64 ticksPerSecond;

/*
 * initializes params of the CNC machine
 */
void CNC_voidInit(
	CNC_t* CNC, GPIO_Pin_t _autoLevelingProbePin, Stepper_t* stepperArr)
{
	/*	store and init auto leveling probe pin as pulled up input	*/
	CNC->autoLevelingProbePin = _autoLevelingProbePin % 16;
	CNC->autoLevelingProbePort = _autoLevelingProbePin / 16;
	GPIO_voidSetPinInputPullUp(
			CNC->autoLevelingProbePort, CNC->autoLevelingProbePin);
	
	/*	store stepperArr	*/
	CNC->stepperArr = stepperArr;
		
	/*
	 * relative positioning and auto leveling are initially turned off, to
	 * activate them, user may command their respective commands.
	 */
	CNC->mainParametersArr[CNC_relativePositioning] = 0;
	CNC->autoLevelingEnable = 0;

	/*	obviously, machine've just started	*/
	CNC->speedCurrent = 0;
	
	/*
	 * storing ticks per second, to avoid the overhead resulted from executing
	 * the function "STK_u32GetTicksPerSecond()" frequently.
	 */
	ticksPerSecond = STK_u32GetTicksPerSecond();
}

/*
 * allows the user to change the current position of the tool in memory,
 * usually used for debugging
 */
void CNC_voidExecuteSoftwareSetPosition(CNC_t* CNC)
{
	for (u8 i=0; i<2; i++)
		CNC->stepperArr[i].currentPos = CNC->point[i];
}

/*
 * takes action on parsed messages
 */
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
			CNC->feedrate =
					msgPtr->paramNumArr[msgPtr->paramCount-1] * STEPS_PER_MM;
			CNC_voidExecuteMovement(CNC, CNC_MOVEMENTTYPE_feed);
			break;

		case G_CODE_autoLeveling:
			G_Code_voidCopyPointAL(CNC->point, msgPtr);
			CNC_voidExecuteAutoLevelingSampling(CNC);
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
			CNC->mainParametersArr[CNC_maxFeedrate] =
				msgPtr->paramNumArr[0] * STEPS_PER_MM;
			break;

		case G_CODE_setAcceleration:
			G_CODE_voidCopyAcceleration(CNC->mainParametersArr, msgPtr);
			break;

		case G_CODE_enableAutoLeveling:
			CNC_voidExecuteRestoreSavedAutoLevelingData(CNC);
			break;
		}
	}
}

/*
 *	called by "CNC_voidExecute()" when movement is commanded.
 */
void CNC_voidExecuteMovement(CNC_t* CNC, CNC_MOVEMENTTYPE_t movementType)
{
	/*	prepare moving parameters	*/
	if (CNC->mainParametersArr[CNC_relativePositioning] == 0)
	{
		CNC->point[X] -= CNC->stepperArr[X].currentPos;
		CNC->point[Y] -= CNC->stepperArr[Y].currentPos;
	}
	
	u32 speed1 = CNC->speedCurrent;
	u32 speed2;
	u32 speedMax = CNC->mainParametersArr[CNC_maxFeedrate];
	u32 acceleration;
	
	if (movementType == CNC_MOVEMENTTYPE_rapid)
	{
		speed2 = 0;
		speedMax *= RAPID_SPEED_MAX_TO_FEED_SPEED_MAX;
		CNC->speedCurrent = 0;
		acceleration = CNC->mainParametersArr[CNC_accelerationRapid];
	}
	else	// if (movementType == CNC_MOVEMENTTYPE_feed)
	{
		speed2 = CNC->feedrate;
		if (speed2 > speedMax)
			speedMax = speed2;
			
		CNC->speedCurrent = speed2;
		acceleration = CNC->mainParametersArr[CNC_accelerationFeed];
	}
	
	/*	move	*/
	if (!CNC->autoLevelingEnable)
	{
		if (CNC->mainParametersArr[CNC_relativePositioning] == 0)
			CNC->point[Z] -= CNC->stepperArr[Z].currentPos;
		
		CNC_voidMove3Axis(
			CNC,
			CNC->point[X], CNC->point[Y], CNC->point[Z],
			speed1, speed2, speedMax, acceleration
			);
		return;
	}
	
	/*	if auto leveling is enabled	*/
	s32 zAbs =
		CNC->point[Z] +
		CNC_s32Depth(
			CNC, CNC->stepperArr[X].currentPos, CNC->stepperArr[Y].currentPos);
	s32 zSteps = zAbs - CNC->stepperArr[Z].currentPos;
	
	if (movementType == CNC_MOVEMENTTYPE_rapid)
	{
		/*
		 * no need to auto level along the movement. (to avoid high speed
		 * movement scattering)
		 */
		CNC_voidMove3Axis(
			CNC,
			CNC->point[X], CNC->point[Y], zSteps,
			speed1, speed2, speedMax, acceleration
			);
		return;
	}
	
	/*	make the z displacement first	*/
	CNC_voidMove3Axis(
		CNC, 0 ,0, zSteps, speed1, speed2, speedMax, acceleration);

	s32 dx, dy;
	
	s32 xMoved = 0;
	s32 yMoved = 0;
	
	s32* largestMovedPtr;
	
	if (labs(CNC->point[X]) > labs(CNC->point[Y]))
	{
		dx =
			CNC->autoLevelingDs * (s32)MATH_s16FindSignOf(CNC->point[X]) /
			AL_GRID_TRIMMER;

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
		dy =
			CNC->autoLevelingDs * (s32)MATH_s16FindSignOf(CNC->point[Y]) /
			AL_GRID_TRIMMER;

		dx = (s32)((s64)dy * (s64)CNC->point[X] / (s64)CNC->point[Y]);
		
		if (dx == 0		&&		CNC->point[X] != 0)
			dx = CNC->point[X];
		
		largestMovedPtr = &yMoved;
	}
	
	u32 speed2Trim = speed1;
	u32 speedMaxTrim = (speed2Trim > CNC->speedCurrent) ?
		speed2Trim : CNC->speedCurrent;
	
	while (
			labs(xMoved) < labs(CNC->point[X])	||
			labs(yMoved) < labs(CNC->point[Y])
		)
	{
		if (labs(xMoved + dx) >= labs(CNC->point[X]))
			dx = CNC->point[X] - xMoved;
			
		if (labs(yMoved + dy) >= labs(CNC->point[Y]))
			dy = CNC->point[Y] - yMoved;
		
		// make the wanted z-axis material-bit distance:
		zAbs =
			CNC->point[Z] + CNC_s32Depth(
				CNC, CNC->stepperArr[X].currentPos +
				dx, CNC->stepperArr[Y].currentPos + dy);

		zSteps = zAbs - CNC->stepperArr[Z].currentPos;
		
		CNC_voidMove3Axis(
			CNC,
			dx, dy, zSteps,
			CNC->speedCurrent, speed2Trim,
			speedMaxTrim, acceleration);
		
		xMoved += dx;
		yMoved += dy;
		
		// periodic change speed:
		if (labs(*largestMovedPtr) % SPEED_CHANGE_DELTA == 0)
		{
			CNC->speedCurrent = speed2Trim;
			
			speed2Trim = CNC_d64GetEstematedSpeed(
				speed1, speed2, speedMax, acceleration,
				CNC->point[X], CNC->point[Y], 0,
				sqrt((s64)xMoved * (s64)xMoved + (s64)yMoved * (s64)yMoved));
				
			speedMaxTrim = (speed2Trim > CNC->speedCurrent) ?
				speed2Trim : CNC->speedCurrent;
		}
	}
}

/*
 * probes a grid on the working area, rules of that grid must be initially
 * received from user and validated.
 */
void CNC_voidExecuteAutoLevelingSampling(CNC_t* CNC)
{
	/*	store and init params	*/
	CNC->autoLevelingEnable = true;

	/*	N = V + 3	(G-Code convential)	*/
	CNC->autoLevelingGridxN = (u8)CNC->point[4] + 3;
	CNC->autoLevelingGridyN = (u8)CNC->point[5] + 3;

	CNC->autoLevelingStartX = CNC->point[0];
	CNC->autoLevelingStartY = CNC->point[2];

	CNC->autoLevelingEndX = CNC->point[1];
	CNC->autoLevelingEndY = CNC->point[3];
	
	CNC->autoLevelingDy =
		(CNC->autoLevelingEndY - CNC->autoLevelingStartY) /
		(s32)(CNC->autoLevelingGridyN - 1);

	CNC->autoLevelingDx =
		(CNC->autoLevelingEndX - CNC->autoLevelingStartX) /
		(s32)(CNC->autoLevelingGridxN - 1);

	CNC->autoLevelingDs =
		(CNC->autoLevelingDx < CNC->autoLevelingEndY) ?
			CNC->autoLevelingDx : CNC->autoLevelingDy;

	/*	store in flash	*/
	/*	first: unlock, erase pages form 55 to 63, select programming mode	*/
	if (FPEC_b8IsLocked())
		FPEC_voidUnlock();
	FPEC_voidEnablePageEraseMode();
	for (u8 i = 55; i < 64; i++)
		FPEC_voidErasePage(i);
	FPEC_voidDisablePageEraseMode();
	FPEC_voidEnableProgrammingMode();
	/*	store N	*/
	FPEC_voidProgramHalfWord(
		FPEC_HALF_WORD_ADDRESS(55, 0), CNC->autoLevelingGridxN);
	FPEC_voidProgramHalfWord(
		FPEC_HALF_WORD_ADDRESS(55, 1), CNC->autoLevelingGridyN);

	/*	store boundaries	*/
	FPEC_voidProgramWord(
		FPEC_HALF_WORD_ADDRESS(55, 2), CNC->autoLevelingStartX);
	FPEC_voidProgramWord(
		FPEC_HALF_WORD_ADDRESS(55, 4), CNC->autoLevelingStartY);

	FPEC_voidProgramWord(FPEC_HALF_WORD_ADDRESS(55, 6), CNC->autoLevelingEndX);
	FPEC_voidProgramWord(FPEC_HALF_WORD_ADDRESS(55, 8), CNC->autoLevelingEndY);

	/*	start probing/sampling	*/
	u8 i = 0;
	u8 j = 0;

	for (
		s32 y=CNC->autoLevelingStartY;
			y<=CNC->autoLevelingEndY;
			y+=CNC->autoLevelingDy
		)
	{
		s32 x;
		s32 dx;
		u8 jFinal;
		/*	at odd lines, take samples from the end back to beginning	*/
		if (i % 2)
		{
			 x = CNC->autoLevelingEndX;
			 dx = -CNC->autoLevelingDx;
			 jFinal = 0;
			 j = CNC->autoLevelingGridxN - 1;
		}
		/*	while even lines are normally sampled from 0 to N - 1	*/
		else
		{
			x = CNC->autoLevelingStartX;
			dx = CNC->autoLevelingDx;
			jFinal = CNC->autoLevelingGridxN - 1;
			j = 0;
		}
		while(1)
		{
			/*	go to that point of (x, y)	*/
			// tool up:
			CNC_voidMove3Axis(
				CNC,
				0, 0, AUTO_LEVELING_UP,
				0, 0,
				RAPID_SPEED_MAX_TO_FEED_SPEED_MAX *
				CNC->mainParametersArr[CNC_maxFeedrate],
				CNC->mainParametersArr[CNC_accelerationRapid]);
			// move to (x, y):
			CNC_voidMove3Axis(
				CNC,
				x - CNC->stepperArr[X].currentPos,
				y - CNC->stepperArr[Y].currentPos,
				0, 0, 0,
				RAPID_SPEED_MAX_TO_FEED_SPEED_MAX *
				CNC->mainParametersArr[CNC_maxFeedrate],
				CNC->mainParametersArr[CNC_accelerationRapid]);

			/*	probe	*/
			CNC_voidProbe(CNC);

			/*	save current z position to ROM	*/
			u32 romAddress =
				FPEC_WORD_ADDRESS(56, i * CNC->autoLevelingGridyN + j);
			FPEC_voidProgramWord(romAddress, CNC->stepperArr[Z].currentPos);

			/*	save current z position to RAM	*/
			CNC->autoLevelingMap[i][j] = CNC->stepperArr[Z].currentPos;

			/*	iteration end checks	*/
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
		RAPID_SPEED_MAX_TO_FEED_SPEED_MAX *
		CNC->mainParametersArr[CNC_maxFeedrate],
		CNC->mainParametersArr[CNC_accelerationRapid]
		);
	CNC_voidMove3Axis(
		CNC,
		-CNC->stepperArr[X].currentPos, -CNC->stepperArr[Y].currentPos,
		AUTO_LEVELING_UP_MAX - CNC->stepperArr[Z].currentPos,
		0, 0,
		RAPID_SPEED_MAX_TO_FEED_SPEED_MAX *
		CNC->mainParametersArr[CNC_maxFeedrate],
		CNC->mainParametersArr[CNC_accelerationRapid]
		);
	CNC_voidMove3Axis(
		CNC,
		0, 0, -CNC->stepperArr[Z].currentPos,
		0, 0,
		RAPID_SPEED_MAX_TO_FEED_SPEED_MAX *
		CNC->mainParametersArr[CNC_maxFeedrate],
		CNC->mainParametersArr[CNC_accelerationRapid]
		);
}

/*
 * restores previously sampled working area. (useful at restoring system after
 * unexpected power reset, as it saves probing time)
 */
void CNC_voidExecuteRestoreSavedAutoLevelingData(CNC_t* CNC)
{
	/*	enable auto leveling	*/
	CNC->autoLevelingEnable = 1;

	/*	read ROM	*/
	/*	N's	*/
	CNC->autoLevelingGridxN =
		FPEC_u16ReadHalfWord(FPEC_HALF_WORD_ADDRESS(55, 0));
	CNC->autoLevelingGridyN =
		FPEC_u16ReadHalfWord(FPEC_HALF_WORD_ADDRESS(55, 1));

	/*	boundaries	*/
	CNC->autoLevelingStartX =
		FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(55, 2));
	CNC->autoLevelingStartY =
			FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(55, 4));
	CNC->autoLevelingEndX = FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(55, 6));
	CNC->autoLevelingEndY = FPEC_u32ReadWord(FPEC_HALF_WORD_ADDRESS(55, 8));

	/*	samples	*/
	for(u8 i = 0; i < CNC->autoLevelingGridyN; i++)
	{
		for(u8 j = 0; j < CNC->autoLevelingGridxN; j++)
		{
			u32 romAddress =
				FPEC_WORD_ADDRESS(56, i * CNC->autoLevelingGridyN + j);
			CNC->autoLevelingMap[i][j] = FPEC_u32ReadWord(romAddress);
		}
	}

	/*	init d's	*/
	CNC->autoLevelingDy =
		(CNC->autoLevelingEndY - CNC->autoLevelingStartY) /
		(s32)(CNC->autoLevelingGridyN - 1);

	CNC->autoLevelingDx =
		(CNC->autoLevelingEndX - CNC->autoLevelingStartX) /
		(s32)(CNC->autoLevelingGridxN - 1);
	CNC->autoLevelingDs =
		(CNC->autoLevelingDx < CNC->autoLevelingEndY) ?
			CNC->autoLevelingDx : CNC->autoLevelingDy;
}

/*
 * applies bilinear interpolation on the depths of the four bounding points of
 * the point (x, y), to estimate its own depth
 */
s32 CNC_s32Depth(CNC_t* CNC, s32 x, s32 y)
{
	/*	Check that x and y are in the scanned grid	*/
	if (
		CNC->autoLevelingStartY > y	||	y > CNC->autoLevelingEndY	||
		CNC->autoLevelingStartX > x	||	x > CNC->autoLevelingEndX
		)
	{
		/*	wrong x and/or y	*/
		CNC_ERR_HANDLER(WRONG_INTERPOLATION_POINT_ERR_CODE);
	}
	
	/*	finding iP, jP	*/
	u8 iP = (u8)((y - CNC->autoLevelingStartY) / CNC->autoLevelingDy);
	u8 jP = (u8)((x - CNC->autoLevelingStartX) / CNC->autoLevelingDx);
	
	/*	finding four surrounding points	*/
	s64 xL = CNC->autoLevelingStartX + ((s32)jP) * CNC->autoLevelingDx;
	s64 yT = CNC->autoLevelingStartY + ((s32)iP) * CNC->autoLevelingDy;
	
	s64 dTL = CNC->autoLevelingMap[iP][jP];
	s64 dTR = CNC->autoLevelingMap[iP][jP+1];
	s64 dBL = CNC->autoLevelingMap[iP+1][jP];
	s64 dBR = CNC->autoLevelingMap[iP+1][jP+1];
	
	/*	Bilinear interpolation	*/
	s64 d =
		dTL * (xL + CNC->autoLevelingDx - x) * (yT + CNC->autoLevelingDy - y) +
		dBL * (x - xL) * (yT + CNC->autoLevelingDy - y) +
		dTR * (xL + CNC->autoLevelingDx - x) * (y - yT) +
		dBR * (x - xL) * (y - yT);
	d /= (((s64)(CNC->autoLevelingDx)) * ((s64)(CNC->autoLevelingDy)));
	return (s32)d;
}

/*
 * calculates the speed at a given point.
 * (used in auto leveled movements)
 */
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
	
	s32 d1 =
		speedMaxSquared / accelerationDoubled -
		speed1Squared / accelerationDoubled;

	s32 d3 =
		speedMaxSquared / accelerationDoubled -
		speed2Squared / accelerationDoubled;
	
	s32 d2 = displacementMagnitude - (d1 + d3);
	if (d2 < 0)
	{
		/*
		 * d2 value is to be divided into two relative parts, each added to d1
		 * or d3 by a calculated weight.
		 */
		s32 d2Half = d2 / 2;
		
		d1 = d1 + d2Half;
		
		d3 = d3 + d2Half;
		
		if (d1 < 0)
			d1 = 0;
		
		if (d3 < 0)
			d3 = 0;
		
		speedMax = sqrt((u64)accelerationDoubled * (u64)d1 + speed1Squared);
		speedMaxSquared = (u64)speedMax * (u64)speedMax;
		
		/*
		 * this d2 can't ever be negative, as this is compensated in the
		 * windows program.
		 */
		//d2 = displacementMagnitude - (d1 + d3);	//	it should be zero, so
													//	won't overhead cal-
													//	culating.
		d2 = 0;
	}
	
	if (dDone < (u32)d1)	// still accelerating:
		return sqrt(speed1Squared + (u64)accelerationDoubled * (u64)dDone);
		
	else if (dDone < (u32)(d1+d2))	// reached speedMax and running by it:
		return speedMax;
		
	else //if (dDone < d1+d2+d3)	// decelerating:
		return sqrt(speedMaxSquared - (u64)accelerationDoubled * (u64)dDone);
}

/*
 * moves the three axis by a certain argumented displacement and speed/accel
 * params
 */
void CNC_voidMove3Axis(
	CNC_t* CNC,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement,
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration
	)
{
	Stepper_t* stepperArr = CNC->stepperArr;
	
	s32 displacementsAbs[3] = {xDisplacement, yDisplacement, zDisplacement};
	
	/*
	 * storing current position to compensate error at the end of movement.
	 * (absolute of error is less than 4 steps)
	 */
	s32 posStart[3] = {
		stepperArr[0].currentPos,
		stepperArr[1].currentPos,
		stepperArr[2].currentPos};
	
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
	s32 d1 =
		speedMaxSquared / accelerationDoubled -
		speed1Squared / accelerationDoubled;

	s32 d3 =
		speedMaxSquared / accelerationDoubled -
		speed2Squared / accelerationDoubled;

	s32 d2 = displacementMagnitude - (d1 + d3);
	
	/*
	 * if maximum value of "speed" in this exact movement is not going to
	 * reach "speedMax"
	 */
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
	
	Stepper_Direction_t dir[3];
	for (u8 i = 0; i < 3; i++)
	{
		dir[i] = (displacementsAbs[i] >= 0) ?
			Stepper_Direction_forward : Stepper_Direction_backward;
		displacementsAbs[i] = labs(displacementsAbs[i]);
	}
	
	u32 dDoneMost = 0;
	u32 dTotalMost;
	u32 dDone[2] = {0, 0};
	u32 dTotal[2];
	
	/*	sort axis by most displacement	*/
	static u8 axisSorted[3] = {0, 1, 2};
	
	for (u8 i=0; i<2; i++)
	{
		for (u8 j=i+1; j<3; j++)
		{
			if (
				displacementsAbs[axisSorted[j]] >
				displacementsAbs[axisSorted[i]]
				)
			{
				u8 temp = axisSorted[j];
				axisSorted[j] = axisSorted[i];
				axisSorted[i] = temp;
			}
		}
	}
	
	u32 mostDisplacementAbs = (u32)displacementsAbs[axisSorted[0]];
	
	u64 deltaTMost =
		(ticksPerSecond * (u64)displacementMagnitude) /
		(u64)displacementsAbs[axisSorted[0]] / (u64)speed;
	
	/*
	 * steps that most displacement magnitude axis should make before other
	 * axis make single one
	 */
	u32 stepsOfMostToStep[2];

	if (displacementsAbs[axisSorted[1]] == 0)
	{
		stepsOfMostToStep[0] = displacementsAbs[axisSorted[0]] + 1;
		// so it never steps.
	}
	else
	{
		stepsOfMostToStep[0] =
			displacementsAbs[axisSorted[0]] / displacementsAbs[axisSorted[1]];
	}

	if (displacementsAbs[axisSorted[2]] == 0)
	{
		stepsOfMostToStep[1] = displacementsAbs[axisSorted[0]] + 1;
		// so it never steps.
	}
	else
	{
		stepsOfMostToStep[1] =
			displacementsAbs[axisSorted[0]] /displacementsAbs[axisSorted[2]];
	}
	
	/*	starting from speed1, accelerate to speedMax	*/
	/*	stepper of most displacement magnitude is the only one to be timed,	*/
	/*	while the other two don't need to, as they depend on the first	*/	
	dTotalMost =
		((u64)d1 * (u64)displacementsAbs[axisSorted[0]]) /
		displacementMagnitude;

	dTotal[0] =
		((u64)d1 * (u64)displacementsAbs[axisSorted[1]]) /
		displacementMagnitude;
	dTotal[1] =
		((u64)d1 * (u64)displacementsAbs[axisSorted[2]]) /
		displacementMagnitude;
		
	while(dDoneMost < dTotalMost	&&		dDoneMost < mostDisplacementAbs)
	{
		/*	take timestamp	*/
		timeCurrent = STK_u64GetElapsedTicks();
		/*	check if it's time to step the most axis	*/
		if (timeCurrent - stepperArr[axisSorted[0]].lastTimeStamp > deltaTMost)
		{
			/*	if so, step it (the most axis)	*/
			Stepper_voidStep(
				stepperArr + axisSorted[0], dir[axisSorted[0]], timeCurrent);
			dDoneMost++;
			for (u8 i = 0; i < 2; i++)
			{
				/*	check if it's time to step the minor axis	*/
				if (dDoneMost % stepsOfMostToStep[i] == 0)
				{
					/*
					 * if so, check if minor stepper still has remaining steps
					 * (precision check)
					 */
					if (dDone[i] < dTotal[i])
					{
						/*
						 * if so, validate that minor stepper does not make
						 * more steps than what its is allowed to, comparing
						 * with current position of the most one.
						 */
						if (
							(u64)dDone[i] <
							(((u64)dDoneMost *
							(u64)displacementsAbs[axisSorted[1+i]]) /
							(u64)displacementsAbs[axisSorted[0]])
						)
						{
							Stepper_voidStep(
								stepperArr + axisSorted[1+i],
								dir[axisSorted[1+i]], timeCurrent);
							dDone[i]++;
						}
					}
				}
			}
		}
		
		/*	change speed every certain configured interval	*/
		if (!(dDoneMost % SPEED_CHANGE_DELTA))
		{
			speed =
				sqrtf(speed1Squared +
				((u64)accelerationDoubled * (u64)dDoneMost *
				(u64)displacementMagnitude) / displacementsAbs[axisSorted[0]]);
			if (speed < SPEED_MIN)
				speed = SPEED_MIN;
			deltaTMost =
					(ticksPerSecond * (u64)displacementMagnitude) /
					(u64)displacementsAbs[axisSorted[0]] / (u64)speed;
		}
	}
	
	/* changing speed in case an interval change did not happen in d1	*/
	speed =
		sqrtf(speed1Squared +
		((u64)accelerationDoubled * (u64)dDoneMost *
		(u64)displacementMagnitude) / displacementsAbs[axisSorted[0]]);
	if (speed < SPEED_MIN)
		speed = SPEED_MIN;
	deltaTMost =
		(ticksPerSecond * (u64)displacementMagnitude) /
		(u64)displacementsAbs[axisSorted[0]] / (u64)speed;
	
	mostDisplacementAbs -= dDoneMost;
	dDoneMost = 0;
	dDone[0] = 0;
	dDone[1] = 0;

	/*	stay on speedMax for d2	*/
	dTotalMost =
		((u64)d2 * (u64)displacementsAbs[axisSorted[0]]) /
		displacementMagnitude;
	dTotal[0] =
		((u64)d2 * (u64)displacementsAbs[axisSorted[1]]) /
		displacementMagnitude;
	dTotal[1] =
		((u64)d2 * (u64)displacementsAbs[axisSorted[2]]) /
		displacementMagnitude;
	
	while(dDoneMost < dTotalMost		&&		dDoneMost < mostDisplacementAbs)
	{
		timeCurrent = STK_u64GetElapsedTicks();
		if (timeCurrent - stepperArr[axisSorted[0]].lastTimeStamp > deltaTMost)
		{
			Stepper_voidStep(
				stepperArr + axisSorted[0], dir[axisSorted[0]], timeCurrent);
			dDoneMost++;
			
			for (u8 i = 0; i < 2; i++)
			{
				if (dDoneMost % stepsOfMostToStep[i] == 0)
				{
					if (dDone[i] < dTotal[i])
					{
						/*
						 * if so, validate that minor stepper does not make
						 * more steps than what its is allowed to, comparing
						 * with current position of the most one.
						 */
						if (
							(u64)dDone[i] <
							(((u64)dDoneMost *
							(u64)displacementsAbs[axisSorted[1+i]]) /
							(u64)displacementsAbs[axisSorted[0]])
						)
						{
							Stepper_voidStep(
								stepperArr + axisSorted[1+i],
								dir[axisSorted[1+i]], timeCurrent);
							dDone[i]++;
						}
					}
				}
			}
		}
	}
	mostDisplacementAbs -= dDoneMost;
	
	dDoneMost = 0;
	dDone[0] = 0;
	dDone[1] = 0;

	/*	starting from speedMax, decelerate to speed2	*/
	
	dTotalMost =
		((u64)d3 * (u64)displacementsAbs[axisSorted[0]]) /
		displacementMagnitude;
	dTotal[0] =
		((u64)d3 * (u64)displacementsAbs[axisSorted[1]]) /
		displacementMagnitude;
	dTotal[1] =
		((u64)d3 * (u64)displacementsAbs[axisSorted[2]]) /
		displacementMagnitude;
	
	while(dDoneMost < dTotalMost	&&		dDoneMost < mostDisplacementAbs)
	{
		timeCurrent = STK_u64GetElapsedTicks();
		if (timeCurrent - stepperArr[axisSorted[0]].lastTimeStamp > deltaTMost)
		{
			Stepper_voidStep(
				stepperArr + axisSorted[0], dir[axisSorted[0]], timeCurrent);
			dDoneMost++;
			
			for (u8 i = 0; i < 2; i++)
			{
				if (dDoneMost % stepsOfMostToStep[i] == 0)
				{
					if (dDone[i] < dTotal[i])
					{
						/*
						 * if so, validate that minor stepper does not make
						 * more steps than what its is allowed to, comparing
						 * with current position of the most one.
						 */
						if (
							(u64)dDone[i] <
							(((u64)dDoneMost *
							(u64)displacementsAbs[axisSorted[1+i]]) /
							(u64)displacementsAbs[axisSorted[0]])
						)
						{
							Stepper_voidStep(
								stepperArr + axisSorted[1+i],
								dir[axisSorted[1+i]], timeCurrent);
							dDone[i]++;
						}
					}
				}
			}
		}
		
		/*	change speed every certain configured interval	*/
		if (!(dDoneMost % SPEED_CHANGE_DELTA))
		{
			speed =
				sqrtf(speedMaxSquared -
				((u64)accelerationDoubled * (u64)dDoneMost *
				(u64)displacementMagnitude) / displacementsAbs[axisSorted[0]]);
			if (speed < SPEED_MIN)
				speed = SPEED_MIN;
			deltaTMost =
				(ticksPerSecond * (u64)displacementMagnitude) /
				(u64)displacementsAbs[axisSorted[0]] / (u64)speed;
		}
	}
	mostDisplacementAbs -= dDoneMost;
	dDoneMost = 0;
	dDone[0] = 0;
	dDone[1] = 0;
	
	/*
	 * compensate precision error.
	 * (for testing purposes only, to find mis-calculations in the
	 * used methods, "error[n]" shall eventually be always zero - after
	 * finishing heavy test on the method)
	 */
	s32 error[3] = {
		xDisplacement - stepperArr[0].currentPos + posStart[0],
		yDisplacement - stepperArr[1].currentPos + posStart[1],
		zDisplacement - stepperArr[2].currentPos + posStart[2]
	};
	
	for (u8 i=0; i<3; i++)
	{
		dir[i] = (error[i] >= 0.0) ?
			Stepper_Direction_forward : Stepper_Direction_backward;
		error[i] = labs(error[i]);
	}
	
	u32 dDone3[3] = {0, 0, 0};
	
	while(
			dDone3[0] < (u32)error[0]	||
			dDone3[1] < (u32)error[1]	||
			dDone3[2] < (u32)error[2]
		)
	{
		timeCurrent = STK_u64GetElapsedTicks();
		for (u8 i = 0; i < 3; i++)
		{
			if (timeCurrent - stepperArr[i].lastTimeStamp > deltaTMost)
			{
				if (dDone3[i] < (u32)error[i])
				{
					Stepper_voidStep(stepperArr + i, dir[i], timeCurrent);
					dDone3[i]++;
				}
			}
		}
	}
}

/*
 * probes at the current position of the tool.
 * (the current position of z-axis after probing, is depth of the sample)
 */
void CNC_voidProbe(CNC_t* CNC)
{
	/*	start lowering the head until contact occurs (first touch)	*/
	/*	assuming pin is pulled up, and contact is when it contacts GND	*/
	u64 timeCurrent = STK_u64GetElapsedTicks();

	u32 steps = 0;
	while(
			GPIO_b8ReadPinDigital(
				CNC->autoLevelingProbePort, CNC->autoLevelingProbePin)
		)
	{
		if (
				timeCurrent - CNC->stepperArr[2].lastTimeStamp >=
				AL_SLOW_SPEED_TICKS_PER_STEP
			)
		{
			Stepper_voidStep(
				&CNC->stepperArr[2], Stepper_Direction_backward, timeCurrent);
			steps++;

			if (steps > MAX_PROBE_STEPS)
			{
				CNC_ERR_HANDLER(MAX_PROBE_EXCEEDED_ERR_CODE);
			}
		}
		
		timeCurrent = STK_u64GetElapsedTicks();
	}
}
