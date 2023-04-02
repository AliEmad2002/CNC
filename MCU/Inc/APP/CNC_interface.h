/*
 * CNC_interface.h
 *
 * Created:		07/20/2022
 * Last Mod:	23/10/2022
 *  Author: Ali Emad Ali
 */ 


#ifndef CNC_INTERFACE_H_
#define CNC_INTERFACE_H_

typedef struct
{
	/**
	 * these following variables, are where data is stored after buffering
	 * and before execution. they all use "second" as time dimension's unit,
	 * "step" as length's dimension's unit. the pointers are to be allocated
	 * per need in the execution functions.
	 **/

	/*
	 * point will be of 3 items in the movement mode, but when auto leveling is
	 * required, 6 items are stored. (these 6 items are mentioned in the auto
	 * leveling function)
	 */
	s32 point[6];
	u32 feedrate;
	u32 speedCurrent;
	u32 mainParametersArr[4];
	Stepper_t* stepperArr;
	DC_Motor_t* spindle;
	
	/*	auto leveling parameters	*/
	b8 autoLevelingEnable;

	u8 autoLevelingProbePin;
	GPIO_PortName_t autoLevelingProbePort;

	u8 autoLevelingGridxN;
	u8 autoLevelingGridyN;
	
	s32 autoLevelingStartX;
	s32 autoLevelingEndX;
	s32 autoLevelingDx;

	s32 autoLevelingStartY;
	s32 autoLevelingEndY;
	s32 autoLevelingDy;

	s32 autoLevelingDs;	// (smaller of dx, dy)
	s32 autoLevelingMap[20][20];

}CNC_t;

typedef enum{
	CNC_maxFeedrate				=	0,
	CNC_accelerationFeed		=	1,
	CNC_accelerationRapid		=	2,
	CNC_relativePositioning		=	3
}CNC_MAINPARAMETERS_INDEXES;

typedef enum{
	CNC_MOVEMENTTYPE_rapid,
	CNC_MOVEMENTTYPE_feed
}CNC_MOVEMENTTYPE_t;

/*
 * initializes params of the CNC machine
 */
void CNC_voidInit(
	CNC_t* CNC, GPIO_Pin_t _autoLevelingProbePin,
	Stepper_t* stepperArr, DC_Motor_t* spindle);

/*
 * allows the user to change the current position of the tool in memory,
 * usually used for debugging
 */
void CNC_voidExecuteSoftwareSetPosition(CNC_t* CNC);

/*
 * takes action on parsed messages
 */
void CNC_voidExecute(CNC_t* CNC, G_Code_Msg_t* msgPtr);

/*
 *	called by "CNC_voidExecute()" when movement is commanded.
 */
void CNC_voidExecuteMovement(CNC_t* CNC, CNC_MOVEMENTTYPE_t movementType);

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
 * applies bilinear interpolation on the depths of the four bounding points of
 * the point (x, y), to estimate its own depth
 */
s32 CNC_s32Depth(CNC_t* CNC, s32 x, s32 y);

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

#endif /* CNC_INTERFACE_H_ */
