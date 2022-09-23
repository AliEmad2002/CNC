/*
 * CNC_interface.h
 *
 * Created: 7/20/2022 11:04:41 PM
 *
 * Copyright (c) 2022, Ali Emad
 * All rights reserved.
 *
 * This source code is licensed under the GPL-style license found in the
 * LICENSE file in the root directory of this source tree. 
 */


#ifndef CNC_INTERFACE_H_
#define CNC_INTERFACE_H_

typedef struct
{
	/*
	 * these following variables, are where data is stored after buffering and before execution.
	 * they all use "second" as time dimension's unit, "step" as length's dimension's unit.
	 * the pointers are to be allocated per need in the execution functions.
	 */
	s32* point;
	u32 feedrate;
	u32 speedCurrent;
	u32** mainParametersPtrArr;
	Stepper_t* stepperArr;
	
	/*	auto leveling parameters	*/
	b8 autoLevelingEnable;

	u8 autoLevelingProbePin;
	DIO_PORT autoLevelingProbePort;

	u8 autoLevelingGridxN;
	u8 autoLevelingGridyN;
	
	s32 autoLevelingStartX;
	s32 autoLevelingEndX;
	s32 autoLevelingDx;

	s32 autoLevelingStartY;
	s32 autoLevelingEndY;
	s32 autoLevelingDy;

	s32 autoLevelingDs;	// (smaller of dx, dy)
	s32** autoLevelingMap;

}CNC_t;

enum CNC_MAINPARAMETERS_INDEXES {
	CNC_maxFeedrate				=	0,
	CNC_accelerationFeed		=	1,
	CNC_accelerationRapid		=	2,
	CNC_relativePositioning		=	3
	};

typedef enum{
	CNC_MOVEMENTTYPE_rapid,
	CNC_MOVEMENTTYPE_feed
}CNC_MOVEMENTTYPE_t;


void CNC_voidInit(CNC_t* CNC, DIO_PIN _autoLevelingProbePin, Stepper_t* stepperArr);

void CNC_voidExecuteSoftwareSetPosition(CNC_t* CNC);

void CNC_voidExecute(CNC_t* CNC, G_Code_Msg_t* msgPtr);

void CNC_voidExecuteMovement(CNC_t* CNC, CNC_MOVEMENTTYPE_t movementType);

void CNC_voidExecuteAutoLeveling(CNC_t* CNC);

void CNC_voidExecuteRestoreSavedAutoLevelingData(CNC_t* CNC);

s32 CNC_s32Depth(CNC_t* CNC, s32 x, s32 y);

u32 CNC_d64GetEstematedSpeed(
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement, u32 dDone
	);

void CNC_voidMove3Axis(
	CNC_t* CNC,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement,
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration
	);

void CNC_voidProbe(CNC_t* CNC);

#endif /* CNC_INTERFACE_H_ */
