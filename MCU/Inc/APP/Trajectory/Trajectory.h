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

	u32 vMax;  // maximum speed.
	u32 accel; // acceleration.
}Trajectory_t;

void Trajectory_voidInit(Trajectory_t* traj, SDC_t* sdc, char* tempFileName);

void Trajectory_voidSetVmax(Trajectory_t* traj, u32 v);
void Trajectory_voidSetAcceleration(Trajectory_t* traj, u32 a);

/*
 * flowchart of this function:
 * https://github.com/AliEmad2002/CNC/issues/7#issuecomment-1518841274
 */
void Trajectory_voidPlanTrajectory(Trajectory_t* traj);



#endif /* INCLUDE_APP_TRAJECTORY_TRAJECTORY_H_ */
