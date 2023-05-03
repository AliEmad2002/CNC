/*
 * Trajectory.h
 *
 *  Created on: May 1, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_TRAJECTORY_TRAJECTORY_H_
#define INCLUDE_APP_TRAJECTORY_TRAJECTORY_H_

#include "SDC_interface.h"

typedef struct{
	s32 x;
	s32 y;
	s32 z;
	u32 v;
}Trajectory_Point_t;

typedef struct{
	SD_Stream_t stream;
	u32 numberOfPoints;
	u32 feedAccel;
	u32 feedrateMax;
}Trajectory_t;

/*
 * Returns point that is at a given index in trajectory object.
 * If index is invalid, it returns an all-zero point.
 */
void Trajectory_voidGetPointAt(Trajectory_t* traj, u32 index, Trajectory_Point_t* p);

/*
 * Sets point that is at a given index in trajectory object.
 * If index is invalid, it does nothing.
 */
void Trajectory_voidSetPointAt(Trajectory_t* traj, u32 index, Trajectory_Point_t* p);

/*
 * Resets trajectory pointers.
 * First point of any trajectory is machines current point.
 */
void Trajectory_voidReset(Trajectory_t* traj, Trajectory_Point_t* pFirst);

/*
 * Adds new point at the end of trajectory object. speed of this point is not calculated,
 * it will be calculated when "Trajectory_voidPlan()" is used.
 */
void Trajectory_voidAddPoint(Trajectory_t* traj, Trajectory_Point_t* p);

/*
 * Plans trajectory based on its points, maximum speed and acceleration.
 * Notice that the first available point in "traj" (if any) must have its speed "v"
 * set to its actual value.
 */
void Trajectory_voidPlan(Trajectory_t* traj);

/*	Prints trajectory points on debugger	*/
void Trajectory_voidPrint(Trajectory_t* traj);

#endif /* INCLUDE_APP_TRAJECTORY_TRAJECTORY_H_ */
