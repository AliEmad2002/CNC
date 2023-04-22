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
	u32 vf;
}Point_t;

/*	vMax is a value that trajectory planning is based on	*/
void Point_voidSetVmax(u32 vMax);

/*
 * flowchart of this function:
 * https://github.com/AliEmad2002/CNC/issues/7#issuecomment-1518841274
 */
void Point_voidPlanTrajectory(Point_t* pArr, u32 pCount);


#endif /* INCLUDE_APP_POINT_POINT_H_ */
