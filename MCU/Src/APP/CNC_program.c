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
#include <cmsis_gcc.h>
#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "My_Math.h"
#include "G_code_interface.h"
#include "Delay_interface.h"
#include "Error_Handler_interface.h"
#include "diag/trace.h"
#include "Trajectory.h"

/*	MCAL	*/
#include "RCC_interface.h"
#include "TIM_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "FPEC_interface.h"
#include "UART_interface.h"

/*	SELF	*/
#include "CNC_private.h"
#include "CNC_config.h"
#include "CNC_interface.h"


static u64 ticksPerSecond;

static s32 mapArr[400];

/*******************************************************************************
 * Static (private) functions:
 ******************************************************************************/
ALWAYS_INLINE_STATIC u8 is_traj_line(char* line)
{
	if (
		line[0] == 'G'		&&
		line[1] == '0'		&&
		line[2] == '1'		&&
		line[3] == ' '		&&
		line[4] != 'F'
	)
		return 1;

	if (
		line[0] == 'G'		&&
		line[1] == '1'		&&
		line[2] == ' '		&&
		line[3] != 'F'
	)
		return 1;

	return 0;
}

/*	Parses and executes the line string available in "CNC->lineStr"	*/
ALWAYS_INLINE_STATIC void parse_execute_line(CNC_t* CNC)
{
	G_Code_Msg_t msg;
	b8 parseSuccess = G_Code_b8ParseLine(&msg, CNC->lineStr);

	/*	if parsing failed, skip this line (comment or empty line)	*/
	if (!parseSuccess)
	{
//		trace_printf("Could not parse G-code line:\n");
//		trace_printf("%s\n", CNC->lineStr);
		return;
	}

	/*	Execute	*/
	CNC_voidExecute(CNC, &msg);
}

static void read_execute_non_traj_chunk(CNC_t* CNC)
{
	u8 isTraj;

	/*	while G-code file still has un-read lines	*/
	while(SDC_u8IsThereNextLine(&(CNC->gcodeFile)))
	{
		/*	read line	*/
		SDC_voidGetNextLine(&(CNC->gcodeFile), CNC->lineStr, MAX_STR_LEN);

		/*	check if it is trajectory related or not	*/
		isTraj = is_traj_line(CNC->lineStr);

		/*	if not, execute it	*/
		if (!isTraj)
		{
			parse_execute_line(CNC);
		}

		/*	otherwise, set "stream->reader" back to first of this last read line, and return	*/
		else
		{
			(void)SDC_u8SeekReaderPrevLine(&(CNC->gcodeFile));
			return;
		}
	}
}

/*	Given y value, it returns x value on the line: {pi, pf}	*/
ALWAYS_INLINE_STATIC s32 get_x_on_line(Trajectory_Point_t* pi, Trajectory_Point_t* pf, u32 y)
{
	s64 d1 = y - pi->y;
	s64 d2 = pf->x - pi->x;
	s64 d3 = pf->y - pi->y;

	s32 x = (d1 * d2) / d3 + pi->x;
	return x;
}

/*	Given x value, it returns y value on the line: {pi, pf}	*/
ALWAYS_INLINE_STATIC s32 get_y_on_line(Trajectory_Point_t* pi, Trajectory_Point_t* pf, u32 x)
{
	s64 d1 = x - pi->x;
	s64 d2 = pf->y - pi->y;
	s64 d3 = pf->x - pi->x;

	s32 y = (d1 * d2) / d3 + pi->y;
	return y;
}

ALWAYS_INLINE_STATIC u64 get_distance_square(s32 x0, s32 x1, s32 y0, s32 y1)
{
	s64 dx = x1 - x0;
	s64 dy = y1 - y0;
	u64 dSquared = dx * dx + dy * dy;
	return dSquared;
}

static u32 get_xy_d(Trajectory_Point_t* pi, Trajectory_Point_t* pf)
{
	s64 dx = pf->x - pi->x;
	s64 dy = pf->y - pi->y;

	u32 d = sqrt(dx*dx + dy*dy);
	return d;
}

/*
 * using {x, y} of "pInter", this function interpolates "pi->z" and "pf->z" to
 * get and write "pInter->z".
 */
static void get_z_inner(Trajectory_Point_t* pi, Trajectory_Point_t* pf, Trajectory_Point_t* pInter)
{
	s64 dTotal = get_xy_d(pi, pf);
	s64 d = get_xy_d(pi, pInter);

	if (dTotal == 0  &&  d == 0)
	{
		pInter->z = pf->z;
		return;
	}

	s64 dz = pf->z - pi->z;
	s64 offset = (dz * d) / dTotal;

	pInter->z = pi->z + (s32)offset;
}

ALWAYS_INLINE_STATIC void get_first_intersection_with_level_grid(
	CNC_t* CNC,
	Trajectory_Point_t* pi, Trajectory_Point_t* pf, Trajectory_Point_t* pInter)
{
	s32 y, x;
	u64 diSquared;

	/*	get yu, yd, xr, xl of the rectangle containing pi	*/
	s32 yOffset = pi->y - CNC->map.sY;
	if (yOffset != 0)
		yOffset--;	// to avoid getting pInter = pi, if pi was exactly on the grid.

	s32 xOffset = pi->x - CNC->map.sX;
	if (xOffset != 0)
		xOffset--;

	s32 yu = (yOffset / CNC->map.dY) * CNC->map.dY + CNC->map.sY;
	s32 xl = (xOffset / CNC->map.dX) * CNC->map.dX + CNC->map.sX;
	s32 yd = yu + CNC->map.dY;
	s32 xr = xl + CNC->map.dX;

	/*	get square of the line length	*/
	u64 dSquared = get_distance_square(pf->x, pi->x, pf->y, pi->y);

	/*	up / down check	*/
	if (pi->y != pf->y)
	{
		if (pi->y > pf->y)	/*	if line is going up	*/
			y = yu;
		else
			y = yd;

		x = get_x_on_line(pi, pf, y);
		diSquared = get_distance_square(pi->x, x, pi->y, y);

		/*	 if point is on the rectangle's Perimeter, and is also inside the line: {pi, pf}	*/
		if (xl <= x  &&  x <= xr  &&  diSquared <= dSquared)
		{
			pInter->x = x;
			pInter->y = y;
			get_z_inner(pi, pf, pInter);
			return;
		}
	}

	/*	right left check	*/
	if (pi->x != pf->x)
	{
		if (pi->x < pf->x)	/*	if line is going right	*/
			x = xr;
		else
			x = xl;

		y = get_y_on_line(pi, pf, x);
		diSquared = get_distance_square(pi->x, x, pi->y, y);

		/*	 if point is on the rectangle's Perimeter, and is also inside the line: {pi, pf}	*/
		if (yu <= y  &&  y <= yd  &&  diSquared <= dSquared)
		{
			pInter->x = x;
			pInter->y = y;
			get_z_inner(pi, pf, pInter);
			return;
		}
	}

	/*	Otherwise, pInter = pf	*/
	pInter->x = pf->x;
	pInter->y = pf->y;
	pInter->z = pf->z;
}

ALWAYS_INLINE_STATIC void get_speed_estimation_params(
	Trajectory_t* traj, Trajectory_Point_t* pi, Trajectory_Point_t* pf,
	u32* ptrSpeedMax, u32* ptrD1, u32* ptrD2)
{
	s64 xDisplacement = pf->x - pi->x;
	s64 yDisplacement = pf->y - pi->y;
	s64 zDisplacement = pf->z - pi->z;

	u32 displacementMagnitude = sqrt(
	xDisplacement * xDisplacement +
	yDisplacement * yDisplacement +
	zDisplacement * zDisplacement
	);

	u64 speed1Squared = (u64)pi->v * (u64)pi->v;
	u64 speed2Squared = (u64)pf->v * (u64)pf->v;
	u64 speedMaxSquared = (u64)traj->feedrateMax * (u64)traj->feedrateMax;
	u32 accelerationDoubled = 2 * traj->feedAccel;

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

		speedMaxSquared = (u64)accelerationDoubled * (u64)d1 + speed1Squared;
		*ptrSpeedMax = sqrt(speedMaxSquared);

		/*
		 * this d2 can't ever be negative, as this is compensated in the
		 * trajectory planning function.
		 */
		//d2 = displacementMagnitude - (d1 + d3);	//	it should be zero, so
													//	won't overhead cal-
													//	culating.
		d2 = 0;
	}
	else
	{
		*ptrSpeedMax = traj->feedrateMax;
	}

	*ptrD1 = (u32)d1;
	*ptrD2 = (u32)d2;
}

ALWAYS_INLINE_STATIC u32 get_estimated_speed(
	Trajectory_Point_t* pi, Trajectory_Point_t* p,
	u32 accel, u32 speedMax, u32 d1, u32 d2)
{
	/*	Calculate the distance: {pi, p}	*/
	s64 xDisplacement = p->x - pi->x;
	s64 yDisplacement = p->y - pi->y;
	s64 zDisplacement = p->z - pi->z;

	u64 dist = sqrt(
	xDisplacement * xDisplacement +
	yDisplacement * yDisplacement +
	zDisplacement * zDisplacement
	);

	/*	Get the estimated speed	*/
	u64 speed1Squared = (u64)pi->v * (u64)pi->v;
	u64 speedMaxSquared = speedMax * speedMax;
	u64 accelerationDoubled = 2 * accel;

	if (dist < d1)	// still accelerating:
		return sqrt(speed1Squared + accelerationDoubled * dist);

	else if (dist < d1 + d2)	// reached speedMax and running by it:
		return speedMax;

	else //if (dDone <= d1+d2+d3)	// decelerating:
		return sqrt(speedMaxSquared - accelerationDoubled * (dist - (d1+d2)));
}

/*
 * Moves the machine from its current position to the given "pf".
 * While moving, level depth interpolation is done.
 *
 * Flowchart of this function:
 * 		https://github.com/AliEmad2002/CNC/issues/8#issue-1696592682
 */
static void move_to(CNC_t* CNC, Trajectory_Point_t* pf)
{
	/*	get initial point (current position of the machine)	*/
	Trajectory_Point_t pi = {
		CNC->stepperArr[0].currentPos,
		CNC->stepperArr[1].currentPos,
		CNC->stepperArr[2].currentPos,
		CNC->speedCurrent
	};

	/*	if auto leveling is not enabled, make the movement at once	*/
	if (CNC->config.autoLevelingEnabled == 0)
	{
		CNC_voidMove3Axis(
			CNC,
			pf->x - pi.x,	/*	dx	*/
			pf->y - pi.y,	/*	dy	*/
			pf->z - pi.z,	/*	dz	*/
			pi.v, pf->v,	/*	vi, vf	*/
			CNC->trajectory.feedrateMax, CNC->trajectory.feedAccel);

		CNC->speedCurrent = pf->v;
		return;
	}

	/*	otherwise, movement is segmented into smaller movements	*/
	/*	prepare speed estimation params	*/
	u32 speedMax, d1, d2;
	get_speed_estimation_params(
		&(CNC->trajectory), &pi, pf, &speedMax, &d1, &d2);

	Trajectory_Point_t pInner0 = pi;

	Trajectory_Point_t pInner1;

	while(1)
	{
		get_first_intersection_with_level_grid(CNC, &pInner0, pf, &pInner1);

		pInner1.v = get_estimated_speed(
			&pi, &pInner1, CNC->trajectory.feedAccel, speedMax, d1, d2);

		s32 zOffset0 = LevelMap_s32GetDepthAt(&(CNC->map), pInner0.x, pInner0.y);
		s32 zOffset1 = LevelMap_s32GetDepthAt(&(CNC->map), pInner1.x, pInner1.y);

		CNC_voidMove3Axis(
			CNC,
			pInner1.x - pInner0.x,								/*	dx	*/
			pInner1.y - pInner0.y,								/*	dy	*/
			(pInner1.z + zOffset1) - (pInner0.z + zOffset0),	/*	dz	*/
			pInner0.v, pInner1.v,								/*	vi, vf	*/
			speedMax, CNC->trajectory.feedAccel);

		if (
			pInner1.x == pf->x	&&
			pInner1.y == pf->y	&&
			pInner1.z == pf->z
			)
			break;

		pInner0 = pInner1;
	}

	CNC->speedCurrent = pInner1.v;
}

static void execute_traj(CNC_t* CNC)
{
	Trajectory_voidPrint(&(CNC->trajectory));
//	while(1);

	Trajectory_Point_t p;

	for (u32 i = 0; i < CNC->trajectory.numberOfPoints; i++)
	{
		Trajectory_voidGetPointAt(&(CNC->trajectory), i, &p);
		move_to(CNC, &p);
	}
}

static void get_point_from_msg(CNC_t* CNC, Trajectory_Point_t *p, G_Code_Msg_t* msg)
{
	/**
	 * Based on "CNC->config", last added point in "CNC->trajectory", and the just
	 * parsed line ("msg" object), set x, y, z of the trajectory point "p"
	 **/
	/*	Copy previous point in trajectory into this point "p"	*/
	Trajectory_voidGetPointAt(&(CNC->trajectory), CNC->trajectory.numberOfPoints - 1, p);

	/*	Edit only values of new received axis	*/
	u8 count = msg->paramCount;
	while(count--)
	{
		u8 pointIndex = msg->paramChArr[count] - 'X';
		((s32*)p)[pointIndex] =
			msg->paramNumArr[count] * (f32)CNC->config.stepsPerLengthUnit[pointIndex];
	}
}

static void read_execute_traj_chunk(CNC_t* CNC)
{
	b8 parseSuccess;
	u8 isTraj;
	Trajectory_Point_t p;
	G_Code_Msg_t msg;

	/*	Get machines current position (initial point of this new trajectory)	*/
	Trajectory_Point_t pFirst = {
		.x = CNC->stepperArr[0].currentPos,
		.y = CNC->stepperArr[1].currentPos,
		.z = CNC->stepperArr[2].currentPos,
		.v = CNC->speedCurrent
	};

	/*	reset reading pointers in trajectory object	*/
	Trajectory_voidReset(&(CNC->trajectory), &pFirst);

	/*	while G-code file still has un-read lines	*/
	while(SDC_u8IsThereNextLine(&(CNC->gcodeFile)))
	{
		/*	read line	*/
		SDC_voidGetNextLine(&(CNC->gcodeFile), CNC->lineStr, MAX_STR_LEN);

		/*	check if it is trajectory related or not	*/
		isTraj = is_traj_line(CNC->lineStr);

		/*	if it is	*/
		if (isTraj)
		{
			/*	parse line	*/
			parseSuccess = G_Code_b8ParseLine(&msg, CNC->lineStr);

			/*	if parsing failed, skip this line (comment or empty line)	*/
			if (!parseSuccess)
			{
//				trace_printf("Could not parse G-code line:\n");
//				trace_printf("%s\n", CNC->lineStr);
				continue;
			}

			/*	Otherwise, copy new point	*/
			get_point_from_msg(CNC, &p, &msg);

			/*	Add point "p" to the trajectory object	*/
			Trajectory_voidAddPoint(&(CNC->trajectory), &p);
		}

		/*	otherwise, set "stream->reader" back to first of this last read line, and break	*/
		else
		{
			(void)SDC_u8SeekReaderPrevLine(&(CNC->gcodeFile));
			break;
		}
	}

	/*	Plan the read trajectory	*/
	//u64 s = STK_u64GetElapsedTicks();
	Trajectory_voidPlan(&(CNC->trajectory));
	//volatile u64 t = STK_u64GetElapsedTicks() - s;

	/*	Execute it	*/
	execute_traj(CNC);
}

static f32 get_uart_num(void)
{
	char str[UART_MAX_STRLEN];
	UART_voidReceiveUntilByte(UART_UNIT_NUMBER, str, '\r');
	return Math_f32StrToFloat(str, 0, strlen(str) - 1);
}

static void tool_change(CNC_t* CNC)
{
	UART_voidSendString(UART_UNIT_NUMBER, "Entered tool change mode\r\n");
	CNC_voidMoveManual(CNC);
	CNC_voidChangeRamPos(CNC);
}

/*******************************************************************************
 * Interface functions:
 ******************************************************************************/
void CNC_voidInit(CNC_t* CNC)
{
	/*	probe	*/
	CNC->probe.port = AUTO_LEVELING_PROBE_PIN / 16;
	CNC->probe.pin  = AUTO_LEVELING_PROBE_PIN % 16;
	CNC->probe.openCirciutLevel = AUTO_LEVELING_PROBE_OC_LEVEL;
	Probe_voidInit(&(CNC->probe));

	/*	steppers	*/
	CNC->stepperArr[0].stepPort = X_STEP_PIN / 16;
	CNC->stepperArr[0].stepPin  = X_STEP_PIN % 16;
	CNC->stepperArr[0].dirPort  = X_DIR_PIN  / 16;
	CNC->stepperArr[0].dirPin   = X_DIR_PIN  % 16;
	Stepper_voidInit(&(CNC->stepperArr[0]));

	CNC->stepperArr[1].stepPort = Y_STEP_PIN / 16;
	CNC->stepperArr[1].stepPin  = Y_STEP_PIN % 16;
	CNC->stepperArr[1].dirPort  = Y_DIR_PIN  / 16;
	CNC->stepperArr[1].dirPin   = Y_DIR_PIN  % 16;
	Stepper_voidInit(&(CNC->stepperArr[1]));

	CNC->stepperArr[2].stepPort = Z_STEP_PIN / 16;
	CNC->stepperArr[2].stepPin  = Z_STEP_PIN % 16;
	CNC->stepperArr[2].dirPort  = Z_DIR_PIN  / 16;
	CNC->stepperArr[2].dirPin   = Z_DIR_PIN  % 16;
	Stepper_voidInit(&(CNC->stepperArr[2]));

	/*	spindle	*/
	DC_Motor_voidInit(
		&(CNC->spindle), SPINDLE_PWM_TIM_UNIT_NUMBER,
		SPINDLE_PWM_TIM_CHANNEL, SPINDLE_PWM_AFIO_MAP);
		
	/*	SD card	*/
	SDC_voidKeepTryingInitConnection(&(CNC->sdCard), 1, SPI_UnitNumber_1, SD_CS_PIN, SD_AFIO_MAP);
	SDC_voidKeepTryingInitPartition(&(CNC->sdCard));

	/*	G-code file	*/
	SDC_voidKeepTryingOpenStream(&(CNC->gcodeFile), &(CNC->sdCard), "FILE.NC");

	/*	Trajectory RFS	*/
	CNC->trajectory.numberOfPoints = 0;
	SDC_voidKeepTryingOpenStream(&(CNC->trajectory.stream), &(CNC->sdCard), "TRAJ.RFS");
	Trajectory_Point_t p = {0, 0, 0, 0};
	Trajectory_voidReset(&(CNC->trajectory), &p);

	/*
	 * relative positioning and auto leveling are initially turned off, to
	 * activate them, user may command their respective commands.
	 */
	CNC->config.relativePosEnabled = 0;
	CNC->config.autoLevelingEnabled = 0;

	/*	unit system is initially metric	*/
	CNC->config.unitSys = 0;

	/*	initial steps per mm	*/
	CNC->config.stepsPerLengthUnit[0] = STEPS_PER_MM;
	CNC->config.stepsPerLengthUnit[1] = STEPS_PER_MM;
	CNC->config.stepsPerLengthUnit[2] = STEPS_PER_MM;

	/*	map	*/
	CNC->map.flashSavingBasePage = AUTO_LEVELING_FLASH_BASE_PAGE;
	CNC->map.mapArr = mapArr;
	for (u16 i = 0; i < 400; i++)
		mapArr[i] = 0;

	/*	obviously, machine've just started	*/
	CNC->speedCurrent = 0;

	/*
	 * storing ticks per second, to avoid the overhead resulted from executing
	 * the function "STK_u32GetTicksPerSecond()" frequently.
	 */
	ticksPerSecond = STK_u32GetTicksPerSecond();
}

void CNC_voidExecuteSoftwareSetPosition(CNC_t* CNC)
{
	for (u8 i = 0; i < 3; i++)
		CNC->stepperArr[i].currentPos = CNC->point[i];
}

void CNC_voidExecute(CNC_t* CNC, G_Code_Msg_t* msgPtr)
{
	if (msgPtr->codeClass == 'G')
	{
		switch (msgPtr->code)
		{
		case G_CODE_rapidMovement:
			/*	if changing speed	*/
			if (msgPtr->paramChArr[0] == 'F')
			{
				CNC->config.rapidSpeedMax =
					msgPtr->paramNumArr[0] *
					(f32)CNC->config.stepsPerLengthUnit[0] / 60.0f;
			}

			/*	if making a movement	*/
			else
			{
				G_Code_voidCopyPoint(msgPtr);
				CNC_voidMove3Axis(
					CNC,
					CNC->point[0] - CNC->stepperArr[0].currentPos,
					CNC->point[1] - CNC->stepperArr[1].currentPos,
					CNC->point[2] - CNC->stepperArr[2].currentPos,
					CNC->speedCurrent, 0,
					CNC->config.rapidSpeedMax, CNC->config.rapidAccel);
			}
			break;

		case G_CODE_feedMovement:
			/*
			 * It is guaranteed in code flow, that this "G_CODE_feedMovement" won't
			 * be executed in this function unless it has only the 'F' parameter.
			 */
			G_Code_voidUpdateFeedRateMax(msgPtr);
			break;

		case G_CODE_imperialUnits:
			CNC_voidUseImperialUnits(CNC);
			break;

		case G_CODE_metricUnits:
			CNC_voidUseMetricUnits(CNC);
			break;

		case G_CODE_autoLeveling:
			G_Code_voidCopyPointAL(msgPtr);
			CNC_voidExecuteAutoLevelingSampling(CNC);
			break;

		case G_CODE_singleProbe:
			CNC_voidProbe(CNC);
			break;

		case G_CODE_abslutePositioning:
			CNC->config.relativePosEnabled = 0;
			break;

		case G_CODE_relativePositioning:
			CNC->config.relativePosEnabled = 1;
			break;

		case G_CODE_softwareSetPosition:
			G_Code_voidCopyPoint(msgPtr);
			CNC_voidExecuteSoftwareSetPosition(CNC);
			break;

		case G_CODE_feedUnitPerMinute:
			/*	do noting, as this is the only one supported so-far	*/
			break;

		default:
			/*	log that a command was not recognized	*/
			trace_printf("command not recognized. please look at \"msgPtr\" before continuing\n");
			u8 cont = 0;
			__BKPT(0);
			while(!cont);
		}
	}
	
	else if (msgPtr->codeClass == 'M')
	{
		switch (msgPtr->code)
		{
		case G_CODE_setSpindleSpeedCW:
			DC_Motor_voidSetSpeed(&(CNC->spindle), msgPtr->paramNumArr[0]);
			break;

		case G_CODE_setSpindleSpeedCCW:
			DC_Motor_voidSetSpeed(&(CNC->spindle), msgPtr->paramNumArr[0]);
			break;

		case G_CODE_turnSpindleOff:
			DC_Motor_voidSetSpeed(&(CNC->spindle), 0);
			break;

		case G_CODE_toolChange:
			tool_change(CNC);
			break;

		case G_CODE_setMaxFeedrate:
			CNC->trajectory.feedrateMax =
				msgPtr->paramNumArr[0] * (f32)CNC->config.stepsPerLengthUnit[0] / 60.0f;
			break;

		case G_CODE_setAcceleration:
			G_CODE_voidCopyAcceleration(msgPtr);
			break;

		case G_CODE_enableAutoLeveling:
			CNC_voidExecuteRestoreSavedAutoLevelingData(CNC);
			break;

		default:
			/*	log that a command was not recognized	*/
			trace_printf("command not recognized. please look at \"msgPtr\" before continuing\n");
			u8 cont = 0;
			__BKPT(0);
			while(!cont);
		}
	}
}

void CNC_voidExecuteAutoLevelingSampling(CNC_t* CNC)
{
	/**
	 * initially probe on (x, y) = (0, 0), and re-set z-displacement variable.
	 * (to achieve re-usability of the same depth map with multiple tools, see
	 * the issue for more details: https://github.com/AliEmad2002/CNC/issues/4)
	 **/
	/*	safety tool up	*/
	CNC_voidMove3Axis(
		CNC, 0, 0, AUTO_LEVELING_UP, 0, 0,
		CNC->config.rapidSpeedMax, CNC->config.rapidAccel);

	/*	(x, y) = (0, 0)	*/
	CNC_voidMove3Axis(
		CNC,
		0 - CNC->stepperArr[X].currentPos,
		0 - CNC->stepperArr[Y].currentPos,
		0, 0, 0,
		CNC->config.rapidSpeedMax, CNC->config.rapidAccel);

	/*	probe	*/
	CNC_voidProbe(CNC);

	/*	reset z-displacement variable	*/
	CNC->stepperArr[Z].currentPos = 0;

	/**	store and init params	**/
	CNC->config.autoLevelingEnabled = 1;

	/*	N = V + 3	(G-Code convention)	*/
	CNC->map.nX = (u8)CNC->point[4] + 3;
	CNC->map.nY = (u8)CNC->point[5] + 3;

	CNC->map.sX = CNC->point[0];
	CNC->map.sY = CNC->point[2];

	CNC->map.eX = CNC->point[1];
	CNC->map.eY = CNC->point[3];
	
	LevelMap_voidInit(&(CNC->map));

	/**	start probing/sampling	**/
	u8 i = 0;
	u8 j = 0;

	/*	y-axis loop	*/
	for (s32 y = CNC->map.sY; y <= CNC->map.eY; y += CNC->map.dY)
	{
		s32 x;
		s32 dx;
		u8 jFinal;
		/*	at odd lines, take samples from the end back to beginning	*/
		if (i % 2)
		{
			 x = CNC->map.eX;
			 dx = -CNC->map.dX;
			 jFinal = 0;
			 j = CNC->map.nX - 1;
		}
		/*	while even lines are normally sampled from 0 to N - 1	*/
		else
		{
			x = CNC->map.sX;
			dx = CNC->map.dX;
			jFinal = CNC->map.nX - 1;
			j = 0;
		}

		/*
		 * x-axis loop.
		 * (This loop is iterated in a little different way than that of y-axis,
		 * because y-axis only goes down, while x-axis will go right in one row,
		 * and go left on the next row, to save hypotenuse displacement time)
		 */
		while(1)
		{
			/*	go to that point of (x, y)	*/
			// tool up:
			CNC_voidMove3Axis(
				CNC, 0, 0, AUTO_LEVELING_UP, 0, 0,
				CNC->config.rapidSpeedMax, CNC->config.rapidAccel);

			// move to (x, y):
			CNC_voidMove3Axis(
				CNC,
				x - CNC->stepperArr[X].currentPos,
				y - CNC->stepperArr[Y].currentPos,
				0, 0, 0,
				CNC->config.rapidSpeedMax, CNC->config.rapidAccel);

			/*	probe	*/
			CNC_voidProbe(CNC);

			/*	save current z position to RAM	*/
			LevelMap_voidSetDepthAt(&(CNC->map), i, j, CNC->stepperArr[Z].currentPos);

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
	
	/**	go home	**/
	/*	safety tool up	*/
	CNC_voidMove3Axis(
		CNC,
		0, 0, AUTO_LEVELING_UP - CNC->stepperArr[Z].currentPos,
		0, 0,
		CNC->config.rapidSpeedMax, CNC->config.rapidAccel);

	/*	go to (x, y) = (0, 0)	*/
	CNC_voidMove3Axis(
		CNC,
		0 					 - CNC->stepperArr[X].currentPos,
		0 					 - CNC->stepperArr[Y].currentPos,
		AUTO_LEVELING_UP_MAX - CNC->stepperArr[Z].currentPos,
		0, 0,
		CNC->config.rapidSpeedMax, CNC->config.rapidAccel);

	/*	tool down	*/
	CNC_voidMove3Axis(
		CNC, 0, 0, -CNC->stepperArr[Z].currentPos, 0, 0,
		CNC->config.rapidSpeedMax, CNC->config.rapidAccel);

	/**	store in flash	**/
	LevelMap_voidStoreToFlash(&(CNC->map));
}

void CNC_voidExecuteRestoreSavedAutoLevelingData(CNC_t* CNC)
{
	/*	enable auto leveling	*/
	CNC->config.autoLevelingEnabled = 1;

	/*	read flash	*/
	LevelMap_voidRestoreFromFlash(&(CNC->map));
}

void CNC_voidGetDistanceMainSegmentsAndUpdateMaximumSpeed(
		s32 dTotal,
		u32 speedStart, u32 speedEnd,
		u32 acceleration,
		s32* d1Ptr, s32* d2Ptr, s32* d3Ptr,
		u32* speedMaxPtr
	)
{
	/**	get square values of speeds first	**/
	u64 speedStartSquared	= (u64)speedStart * (u64)speedStart;
	u64 speedEndSquared		= (u64)speedEnd * (u64)speedEnd;
	u64 speedMaxSquared		= (u64)(*speedMaxPtr) * (u64)(*speedMaxPtr);

	/**	calculate d1	**/
	/*	check the edge case first	*/
	if (speedStart > *speedMaxPtr)
	{
		/*	d1 does not exist	*/
		*d1Ptr = 0;

		/*	maximum speed is the starting	*/
		*speedMaxPtr = speedStart;
		speedMaxSquared = speedStartSquared;
	}

	/*	otherwise	*/
	else
	{
		*d1Ptr = (speedMaxSquared - speedStartSquared) / (u64)(2 * acceleration);
	}

	/**	calculate d3	**/
	/*	check the edge case first	*/
	if (speedEnd > *speedMaxPtr)
	{
		/*	d3 does not exist	*/
		*d3Ptr = 0;

		/*	maximum speed is the ending	*/
		*speedMaxPtr = speedEnd;
		speedMaxSquared = speedEndSquared;
	}

	/*	otherwise	*/
	else
	{
		*d3Ptr = (speedMaxSquared - speedEndSquared) / (u64)(2 * acceleration);
	}

	/**	calculate d2	**/
	/*	check the edge case first	*/
	if (*d1Ptr + *d3Ptr > dTotal)
	{
		/*	d2 does not exist	*/
		*d2Ptr = 0;

		/*
		 * maximum speed is the value that makes no d2 (see explanation pdf file,
		 * mentioned in function description above).
		 */
		speedMaxSquared =
			(u64)acceleration * (u64)dTotal +
			(u64)(speedStartSquared + speedEndSquared) / 2;

		*speedMaxPtr = sqrt(speedMaxSquared);

		/*	recalculate d1 & d3 based on the new speedMax	*/
		*d1Ptr = (speedMaxSquared - speedStartSquared) / (u64)(2 * acceleration);

		*d3Ptr = (speedMaxSquared - speedEndSquared) / (u64)(2 * acceleration);
	}

	/*	otherwise	*/
	else
	{
		*d2Ptr = dTotal - (*d1Ptr + *d3Ptr);
	}
}

/*	Normalizes displacement vector	*/
s32 CNC_s32GetNorm(s32 displacementArr[3])
{
	return (s32)sqrt(
		(s64)displacementArr[0] * (s64)displacementArr[0] +
		(s64)displacementArr[1] * (s64)displacementArr[1] +
		(s64)displacementArr[2] * (s64)displacementArr[2]
		);
}

void CNC_voidMove3Axis(
	CNC_t* CNC,
	s32 xDisplacement, s32 yDisplacement, s32 zDisplacement,
	u32 speed1, u32 speed2, u32 speedMax, u32 acceleration
	)
{
	/*	Extracting stepper CNC->array (for readability only)	*/
	Stepper_t* stepperArr = CNC->stepperArr;
	
	/*
	 * grouping displacement three components in an array (to be absoluted next)
	 */
	s32 displacementsAbs[3] = {xDisplacement, yDisplacement, zDisplacement};
	
	/*
	 * storing current position to compensate error at the end of movement.
	 * (absolute of error is less than 4 steps)
	 */
	s32 posStart[3] = {
		stepperArr[0].currentPos,
		stepperArr[1].currentPos,
		stepperArr[2].currentPos};
	
	/*	magnitude of the distance to be moved	*/
	s32 displacementMagnitude = CNC_s32GetNorm(displacementsAbs);
	
	/*
	 * Calculating distances of different types of acceleration.
	 * (using Newton's movement equations)
	 *
	 * 	-	'd1' is along which the machine accelerates.
	 * 	-	'd2' is along which the machine keeps a constant speed.
	 * 	-	'd3' is along which the machine decelerates.
	 */
	s32 d1, d2, d3;
	
	CNC_voidGetDistanceMainSegmentsAndUpdateMaximumSpeed(
		displacementMagnitude, speed1, speed2, acceleration,
		&d1, &d2, &d3, &speedMax);

	/*	storing heavily repeated calculations	*/
	u64 speed1Squared = (u64)speed1 * (u64)speed1;
	u64 speedMaxSquared = (u64)speedMax * (u64)speedMax;
	u32 accelerationDoubled = 2 * acceleration;
	
	volatile u32 speed = (speed1 < SPEED_MIN) ? SPEED_MIN : speed1;					//	Should it still?
	
	/*	current count of sysTick ticks	*/
	volatile u64 timeCurrent;
	
	/*
	 * get direction of each stepper (based on sign of its displacement).
	 * and absolute "displacementsAbs[]"
	 */
	Stepper_Direction_t dir[3];

	for (u8 i = 0; i < 3; i++)
	{
		if (displacementsAbs[i] >= 0)
		{
			dir[i] = Stepper_Direction_forward;
		}

		else
		{
			dir[i] = Stepper_Direction_backward;
			displacementsAbs[i] = -displacementsAbs[i];
		}
	}
	
	/*	sort axis descendingly based displacement absolute	*/
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
	
	/**
	 * Stepping is going to be in the following way:
	 * 	-	Stepper of most displacement makes a step (in its certain current speed).
	 * 	-	Other two steppers follow.
	 **/

	/*	get displacement of the maximumly moving axis	*/
	u32 mostDisplacementAbs = (u32)displacementsAbs[axisSorted[0]];
	
	/*	time between steps of the maximumly moving axis	*/
	u64 deltaTMost =
		(ticksPerSecond * (u64)displacementMagnitude) /
		(u64)displacementsAbs[axisSorted[0]] / (u64)speed;
	
	/*
	 * steps that most displacement magnitude axis should make before other
	 * axis make single one
	 */
	u32 stepsOfMostToStep[2];

	/*	edge case (to avoid "%" by zero)	*/
	if (displacementsAbs[axisSorted[1]] == 0)
	{
		stepsOfMostToStep[0] = displacementsAbs[axisSorted[0]] + 1;
		// so it never steps.
	}

	/*	otherwise	*/
	else
	{
		stepsOfMostToStep[0] =
			displacementsAbs[axisSorted[0]] / displacementsAbs[axisSorted[1]];
	}

	/*	edge case (to avoid "%" by zero)	*/
	if (displacementsAbs[axisSorted[2]] == 0)
	{
		stepsOfMostToStep[1] = displacementsAbs[axisSorted[0]] + 1;
		// so it never steps.
	}

	/*	otherwise	*/
	else
	{
		stepsOfMostToStep[1] =
			displacementsAbs[axisSorted[0]] /displacementsAbs[axisSorted[2]];
	}

	/*
	 * Number of steps the most displacement stepper have done so far in the
	 * current displacement segment (d1, d2 or d3).
	 */
	u32 dDoneMost = 0;

	/*
	 * Number of steps the most displacement stepper have to travel in the
	 * current displacement segment (d1, d2 or d3).
	 */
	u32 dTotalMost;

	/*
	 * Number of steps the two other steppers have done so far in the current
	 * displacement segment (d1, d2 or d3).
	 */
	u32 dDone[2] = {0, 0};

	/*	Number of steps the two other steppers have to travel in the current
	 * displacement segment (d1, d2 or d3).
	 */
	u32 dTotal[2];
	
	/**
	 * Starting from speed1, accelerate to speedMax.
	 * Stepper of most displacement magnitude is the only one to be timed,
	 * while the other two don't need to, as they depend on the first.
	 **/
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
	
	/*
	 * after d1 is done, changing speed in case an interval change did not
	 * happen in d1.
	 * (i.e.: dDoneMost < SPEED_CHANGE_DELTA)
	 */
	speed =
		sqrtf(speed1Squared +
		((u64)accelerationDoubled * (u64)dDoneMost *
		(u64)displacementMagnitude) / displacementsAbs[axisSorted[0]]);

	if (speed < SPEED_MIN)
		speed = SPEED_MIN;

	deltaTMost =
		(ticksPerSecond * (u64)displacementMagnitude) /
		(u64)displacementsAbs[axisSorted[0]] / (u64)speed;
	
	/*	subtract to done steps from the total displacement to be traveled	*/
	mostDisplacementAbs -= dDoneMost;

	/*	reset done steps. (as d2 has not yet started)	*/
	dDoneMost = 0;

	dDone[0] = 0;

	dDone[1] = 0;

	/**
	 * stay on speedMax for d2.
	 **/
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

	/*	subtract to done steps from the total displacement to be traveled	*/
	mostDisplacementAbs -= dDoneMost;
	
	/*	reset done steps. (as d3 has not yet started)	*/
	dDoneMost = 0;

	dDone[0] = 0;

	dDone[1] = 0;

	/**
	 * starting from speedMax, decelerate to speed2.
	 **/
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

	/*	subtract to done steps from the total displacement to be traveled	*/
	mostDisplacementAbs -= dDoneMost;
	
	/**
	 * compensate precision error.
	 * (for testing purposes only, to find mis-calculations in the
	 * used methods, "error[n]" shall eventually be always zero - after
	 * finishing heavy test on the method)
	 **/
	s32 error[3] = {
		xDisplacement - stepperArr[0].currentPos + posStart[0],
		yDisplacement - stepperArr[1].currentPos + posStart[1],
		zDisplacement - stepperArr[2].currentPos + posStart[2]
	};
	
	/*
	 * get direction of error compensation in each axis, and absolute of the
	 * error value.
	 */
	for (u8 i=0; i<3; i++)
	{
		if (error[i] >= 0.0)
		{
			dir[i] = Stepper_Direction_forward;
		}

		else
		{
			dir[i] = Stepper_Direction_backward;
			error[i] = -error[i];
		}
	}
	
	/*	Number of done steps so far in the error compensation	*/
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

void CNC_voidProbe(CNC_t* CNC)
{
	/**
	 * Start lowering the head until contact occurs (first touch).
	 * Initially, pin must be pulled up and PCB must be grounded.
	 **/

	/*	current time (from sysTick)	*/
	u64 timeCurrent = STK_u64GetElapsedTicks();

	/*	number of steps made so far	*/
	u32 steps = 0;

	/*	current state of the probe pin	*/
	u8 probePinCurrentState = Probe_u8GetStatus(&(CNC->probe));

	/*	as long as the probe circuit is still open	*/
	while(probePinCurrentState == Probe_State_OpenCircuit)
	{
		/*	time passed since previous step in Z-axis	*/
		u64 timeSincePrevStep = timeCurrent - CNC->stepperArr[2].lastTimeStamp;

		/*
		 * if it is time to step the z axis (based on the configured
		 * "AL_SLOW_SPEED_TICKS_PER_STEP")
		 */
		if (timeSincePrevStep >= AL_SLOW_SPEED_TICKS_PER_STEP)
		{
			/*	step the Z-axis down	*/
			Stepper_voidStep(
				&CNC->stepperArr[2], Stepper_Direction_backward, timeCurrent);

			/*	increment step counter	*/
			steps++;

			/*
			 * if that step counter exceeds safety margin, execute error handler.
			 */
//			if (steps > MAX_PROBE_STEPS)
//			{
//				trace_printf("Safe porping limit reached!\n");
//				while(1);
//			}
		}
		
		/*	update probe pin current state	*/
		probePinCurrentState = Probe_u8GetStatus(&(CNC->probe));

		/*	update current timestamp	*/
		timeCurrent = STK_u64GetElapsedTicks();
	}
}

void CNC_voidUseImperialUnits(CNC_t* CNC)
{
	/*	if imperial units are already in use	*/
	if (CNC->config.unitSys == 1)
	{
		/*	do nothing	*/
		return;
	}

	/*	otherwise, convert the steps_per_unit vector	*/
	CNC->config.unitSys = 1;

	for (u8 i = 0; i < 3; i++)
	{
		CNC->config.stepsPerLengthUnit[i] *= 0.0393701f;
	}
}

void CNC_voidUseMetricUnits(CNC_t* CNC)
{
	/*	if metric units are already in use	*/
	if (CNC->config.unitSys == 0)
	{
		/*	do nothing	*/
		return;
	}

	/*	otherwise, convert the steps_per_unit vector	*/
	CNC->config.unitSys = 0;

	for (u8 i = 0; i < 3; i++)
	{
		CNC->config.stepsPerLengthUnit[i] *= 25.4f;
	}
}

void CNC_voidMoveManual(CNC_t* CNC)
{
	char ch;

	UART_voidSendString(UART_UNIT_NUMBER, "Entered manual movement mode\r\n");
	UART_voidSendString(UART_UNIT_NUMBER, "use w, s, a, d, q, e for movement and 0 for exit\r\n");

	while(1)
	{
		UART_enumReciveByte(UART_UNIT_NUMBER, &ch);

		switch(ch)
		{
		case 'w':
			CNC_voidMove3Axis(
				CNC, 0, -200, 0,
				CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax,
				CNC->config.rapidAccel);
			break;

		case 's':
			CNC_voidMove3Axis(
				CNC, 0, 200, 0,
				CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax,
				CNC->config.rapidAccel);
			break;

		case 'a':
			CNC_voidMove3Axis(
				CNC, -200, 0, 0,
				CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax,
				CNC->config.rapidAccel);
			break;

		case 'd':
			CNC_voidMove3Axis(
				CNC, 200, 0, 0,
				CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax,
				CNC->config.rapidAccel);
			break;

		case 'q':
			CNC_voidMove3Axis(
				CNC, 0, 0, -200,
				CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax,
				CNC->config.rapidAccel);
			break;

		case 'e':
			CNC_voidMove3Axis(
				CNC, 0, 0, 200,
				CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax, CNC->config.rapidSpeedMax,
				CNC->config.rapidAccel);
			break;

		case '0':
			return;
		}
	}
}

void CNC_voidChangeRamPos(CNC_t* CNC)
{
	char ch;

	UART_voidSendString(UART_UNIT_NUMBER, "Change x-RAM pos? (y/else): ");
	UART_enumReciveByte(UART_UNIT_NUMBER, &ch);
	if (ch == 'y')
	{
		UART_voidSendString(UART_UNIT_NUMBER, "\r\nEnter x: ");
		CNC->stepperArr[0].currentPos = get_uart_num() * CNC->config.stepsPerLengthUnit[0];
	}

	UART_voidSendString(UART_UNIT_NUMBER, "\r\nChange y-RAM pos? (y/else): ");
	UART_enumReciveByte(UART_UNIT_NUMBER, &ch);
	if (ch == 'y')
	{
		UART_voidSendString(UART_UNIT_NUMBER, "\r\nEnter y: ");
		CNC->stepperArr[1].currentPos = get_uart_num() * CNC->config.stepsPerLengthUnit[1];
	}

	UART_voidSendString(UART_UNIT_NUMBER, "\r\nChange z-RAM pos? (y/else): ");
	UART_enumReciveByte(UART_UNIT_NUMBER, &ch);
	if (ch == 'y')
	{
		UART_voidSendString(UART_UNIT_NUMBER, "\r\nEnter z: ");
		CNC->stepperArr[2].currentPos = get_uart_num() * CNC->config.stepsPerLengthUnit[2];
	}
}

void CNC_voidRunGcodeFile(CNC_t* CNC)
{
	/*	while G-code file still has un-read lines	*/
	while(SDC_u8IsThereNextLine(&(CNC->gcodeFile)))
	{
		/*
		 * Read non trajectory code chunk (starting from the first un-read line),
		 * parse and execute them:
		 */
		read_execute_non_traj_chunk(CNC);

		/*	Read and execute trajectory chunk (starting from the first un-read line)	*/
		read_execute_traj_chunk(CNC);
	}
}

u8 CNC_u8AskNew(CNC_t* CNC)
{
	char ch;

	UART_voidSendString(UART_UNIT_NUMBER, "Make new operation from \"FILE.NC\"? (y/else): ");
	UART_enumReciveByte(UART_UNIT_NUMBER, &ch);
	return (ch == 'y');
}


























