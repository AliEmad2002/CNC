/*
 * Point.h
 *
 *  Created on: Apr 22, 2023
 *      Author: Ali Emad
 */

#ifndef INCLUDE_APP_POINT_POINT_H_
#define INCLUDE_APP_POINT_POINT_H_


typedef struct{
	s32 x;
	s32 y;
	s32 z;
	u32 v;
}PathPoint_t;

/*	"vMax" and "accel" are value on which trajectory planning is based.	*/
void Point_voidSetVmax(u32 vMax);
void Point_voidSetAccel(u32 a);

/*
 * flowchart of this function:
 * https://github.com/AliEmad2002/CNC/issues/7#issuecomment-1518841274
 */
void Point_voidPlanTrajectory(RFS_t* pRfs);


#endif /* INCLUDE_APP_POINT_POINT_H_ */
