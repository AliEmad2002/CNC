/*
 * CNC_interface.h
 *
 * Created:		07/20/2022
 * Last Mod:	23/10/2022
 *  Author: Ali Emad Ali
 */ 


#ifndef CNC_INTERFACE_H_
#define CNC_INTERFACE_H_

#include "RCC_interface.h"
#include "TIM_interface.h"
#include "GPIO_interface.h"

#include "Stepper_interface.h"
#include "DC_Motor_Interface.h"
#include "Probe.h"
#include "SDC_interface.h"

#include "G_code_interface.h"
#include "CNC_config.h"
#include "LevelMap.h"
#include "Trajectory.h"

typedef struct
{
	/**
	 * all of the following parameters use "second" as time dimension's unit,
	 * "step" as length's dimension's unit.
	 **/
	u32 rapidSpeedMax;
	u32 rapidAccel;

	u8 relativePosEnabled : 1;
	u8 autoLevelingEnabled : 1;
	u8 unitSys : 1;	// 0: metric, 1: imperial.

	/** notice that 'LengthUnit' could be either mm or inch	**/
	u32 stepsPerLengthUnit[3];
}CNC_Config_t;


typedef struct
{
	/**
	 * all of the following parameters use "second" as time dimension's unit,
	 * "step" as length's dimension's unit.
	 **/
	Stepper_t stepperArr[3];
	s32 prevReceivedCoordinates[3];
	s32 lastCmdZ;

	DC_Motor_t spindle;

	CNC_Config_t config;

	s32 point[6];

	u32 speedCurrent;
	
	LevelMap_t map;
	
	Probe_t probe;

	SDC_t sdCard;
	SD_Stream_t gcodeFile;
	SD_Stream_t systemState;

	Trajectory_t trajectory;

	char lineStr[MAX_STR_LEN];
}CNC_t;

typedef enum{
	CNC_MovementType_rapid,
	CNC_MovementType_feed
}CNC_MovementType_t;


void CNC_voidInit(CNC_t* CNC);

/*
 * allows the user to change the current position of the tool in memory.
 */
void CNC_voidExecuteSoftwareSetPosition(CNC_t* CNC);

/*
 * takes action on parsed messages
 */
void CNC_voidExecute(CNC_t* CNC, G_Code_Msg_t* msgPtr);

/*
 *	called by "CNC_voidExecute()" when movement is commanded.
 */
void CNC_voidExecuteMovement(CNC_t* CNC, CNC_MovementType_t movementType);

/*
 * probes a grid on the working area, rules of that grid must be initially
 * received from user and validated.
 */
void CNC_voidExecuteAutoLevelingSampling(CNC_t* CNC);

/*
 * restores previously sampled working area. (useful at restoring system after
 * unexpected power reset, as it saves probing time)
 */
void CNC_voidExecuteRestoreSavedAutoLevelingData(CNC_t* CNC);

/*
 * Scans the level map in fast mode (scanning needed areas only) for the currently
 * opened .NC file.
 */
void CNC_voidExecuteFastAutoLevelingSampling(CNC_t* CNC);

/*
 * calculates the speed at a given point.
 * (used in auto leveled movements)
 */
u32 CNC_d64GetEstematedSpeed(
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement, u32 dDone
	);

/*
 * Gets d1, d2, d3, and updates maximum speed (if needed) based on Newton's
 * distance, speed, acceleration equation. Further description and math explanation
 * at: "when to accelerate, keep speed and decelerate.pdf" in notes folder in this
 * repository.
 */
void CNC_voidGetDistanceMainSegmentsAndUpdateMaximumSpeed(
		s32 dTotal,
		u32 speedStart, u32 speedEnd,
		u32 acceleration,
		s32* d1Ptr, s32* d2Ptr, s32* d3Ptr,
		u32* speedMaxPtr
	);

/*	Normalizes displacement vector	*/
s32 CNC_s32GetNorm(s32 displacementArr[3]);

/*
 * moves the three axis by a certain argumented displacement and speed/accel
 * params
 */
void CNC_voidMove3Axis(
	CNC_t* CNC,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement,
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration
	);

/*
 * probes at the current position of the tool.
 * (the current position of z-axis after probing, is depth of the sample)
 */
void CNC_voidProbe(CNC_t* CNC);

void CNC_voidUseImperialUnits(CNC_t* CNC);

void CNC_voidUseMetricUnits(CNC_t* CNC);

/*	makes manual movement	*/
void CNC_voidMoveManual(CNC_t* CNC);

/*	Changes RAM stored position	*/
void CNC_voidChangeRamPos(CNC_t* CNC);

/*	starts executing "FILE.NC" G-code file	*/
void CNC_voidRunGcodeFile(CNC_t* CNC);

/*
 * Asks user if they want to do a new operation.
 * Returns 1 if they do. 0 otherwise.
 */
 /*	TODO: use USB or debugger "printf()" and "scanf()", do HW UI later	*/
u8 CNC_u8AskNew();

u8 CNC_u8AskFastScanMap();

void CNC_voidInfProbing(CNC_t* CNC);

#endif /* CNC_INTERFACE_H_ */
