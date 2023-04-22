/*
 * Point.c
 *
 *  Created on: Apr 22, 2023
 *      Author: Ali Emad
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include <math.h>

/*	SELF	*/
#include "Point.h"

static u32 vMax = 0;

void Point_voidSetVmax(u32 v)
{
	vMax = v;
}

/*	returns sin(theta_b/2)	*/
ALWAYS_INLINE_STATIC f32 get_sin_half_theta_b(Point_t* a, Point_t* b, Point_t* c)
{
	s32 xa = a->x;
	s32 xb = b->x;
	s32 xc = c->x;

	s32 ya = a->y;
	s32 yb = b->y;
	s32 yc = c->y;

	float m1 = (float)(ya - yb) / (float)(xa - xb);
	float m2 = (float)(yb - yc) / (float)(xb - xc);

	float tanTheta = fabs((m1 - m2) / (1.0f + m1*m2));

	float cosTheta = sqrt(1.0f / (1.0f + tanTheta*tanTheta));

	float sinHalfTheta = sqrt((1.0f - cosTheta) / 2.0f);
	return sinHalfTheta;
}

static u32 get_vb(Point_t* a, Point_t* b, Point_t* c)
{
	return (u32)(((f32)vMax) * get_sin_half_theta_b(a, b, c));
}

/*
 * flowchart of this function:
 * https://github.com/AliEmad2002/CNC/issues/7#issuecomment-1518841274
 */
void Point_voidPlanTrajectory(Point_t* pArr, u32 pCount)
{

}














