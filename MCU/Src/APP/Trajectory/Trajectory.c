/*
 * Trajectory.c
 *
 *  Created on: May 1, 2023
 *      Author: Ali Emad
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include <math.h>

/*	HAL	*/
#include "SDC_interface.h"

/*	SELF	*/
#include "Trajectory.h"

/*******************************************************************************
 * Static (private) functions:
 ******************************************************************************/
/*	returns sin(theta_b/2)	*/
ALWAYS_INLINE_STATIC f32 get_sin_half_theta_b(Trajectory_Point_t* a, Trajectory_Point_t* b, Trajectory_Point_t* c)
{
	volatile s32 xa = a->x;
	volatile s32 xb = b->x;
	volatile s32 xc = c->x;

	volatile s32 ya = a->y;
	volatile s32 yb = b->y;
	volatile s32 yc = c->y;

//	f32 m1 = (float)(ya - yb) / (f32)(xa - xb);
//	f32 m2 = (float)(yb - yc) / (f32)(xb - xc);
//	f32 tanTheta = fabs((m1 - m2) / (1.0f + m1*m2));

	volatile s64 dxAB = xa - xb;
	volatile s64 dyAB = ya - yb;
	volatile s64 dxBC = xb - xc;
	volatile s64 dyBC = yb - yc;

	volatile s64 num = dyAB * dxBC - dyBC * dxAB;
	volatile s64 den = dxAB * dxBC - dyBC * dyAB;

	volatile f32 cosTheta;
	if (den == 0)
	{
		cosTheta = 0.0f;
	}
	else
	{
		volatile f32 tanTheta = fabs((f32)num / (f32)den);
		cosTheta = sqrt(1.0f / (1.0f + tanTheta*tanTheta));
	}

	volatile f32 sinHalfTheta = sqrt((1.0f - cosTheta) / 2.0f);
	return sinHalfTheta;
}

/*	returns speed of point b, based on maximum speed and angle between the lines ab, bc	*/
static u32 get_vb(Trajectory_t* traj, Trajectory_Point_t* a, Trajectory_Point_t* b, Trajectory_Point_t* c)
{
	return (u32)(((f32)(traj->feedrateMax)) * get_sin_half_theta_b(a, b, c));
}

/*	returns magnitude of distance between two points	*/
static u32 get_distance_between(Trajectory_Point_t* a, Trajectory_Point_t* b)
{
	s32 dx = a->x - b->x;
	s32 dy = a->y - b->y;

	u64 distSquared = (u64)dx * (u64)dx + (u64)dy * (u64)dy;
	u32 dist = (u32)sqrt(distSquared);
	return dist;
}

/*
 * Checks if acceleration settings can change va to vb in the distance between
 * them.
 *
 * Returns 1 if valid. 0 otherwise.
 */
static u8 is_valid_transition(Trajectory_t* traj, Trajectory_Point_t* a, Trajectory_Point_t* b)
{
	u64 x = get_distance_between(a, b);

	u64 va = a->v;
	u64 vb = b->v;

	u64 accel = traj->feedAccel;

	if (vb > va)
	{
		u64 vfSquared = va * va + 2ul * accel * x;
		if (vfSquared >= vb * vb)
			return 1;
		else
			return 0;
	}

	else if (vb < va)
	{
		s64 vfSquared = va * va - 2 * accel * x;
		if (vfSquared <= vb * vb)
			return 1;
		else
			return 0;
	}

	else
		return 1;
}

/*
 * returns maximum possible speed at point b. that is, the final speed if machine
 * started at point a and kept accelerating until it reaches point b.
 */
static u32 get_max_possible_vb(Trajectory_t* traj, Trajectory_Point_t* a, Trajectory_Point_t* b)
{
	u64 x = get_distance_between(a, b);
	u64 va = a->v;

	u64 accel = traj->feedAccel;

	u64 vmaxSquared = va * va + 2 * accel * x;
	u32 vmax = (u32)sqrt(vmaxSquared);
	return vmax;
}

/*
 * returns maximum possible speed at point a. that is, the initial speed if machine
 * started at point a and kept accelerating until it reaches point b.
 */
static u32 get_max_possible_va(Trajectory_t* traj, Trajectory_Point_t* a, Trajectory_Point_t* b)
{
	return get_max_possible_vb(traj, b, a);
}

///*
// * Optimizes speeds of points prior to the i-th point (if needed) to to achieve
// * smoothest trajectory possible.
// */
//static void optimize_previous(Trajectory_t* traj, u32 i)
//{
//
//}

/*
 * Calculates speed of point number 'i' (Speeds of the point before it must be calculated)
 * and optimizes speeds of previous points (if needed) to to achieve smoothest trajectory
 * possible.
 *
 * Flowchart of this function:
 * https://github.com/AliEmad2002/CNC/issues/7#issuecomment-1518841274
 */
static void calculate_and_optimize(Trajectory_t* traj, u32 i)
{
	/*
	 * Extract points P(i-1), Pi and P(i+1) from the trajectory object to points
	 * a, b, c respectively.
	 */
	Trajectory_Point_t a, b, c;
	Trajectory_voidGetPointAt(traj, i - 1, &a);
	Trajectory_voidGetPointAt(traj, i    , &b);
	Trajectory_voidGetPointAt(traj, i + 1, &c);

	/*	calculate vb and save it back to trajectory object	*/
	b.v = get_vb(traj, &a, &b, &c);
	Trajectory_voidSetPointAt(traj, i, &b);

	/*	optimize from Pi back to P1, or until a first valid transition is achieved	*/
	while(i >= 1)
	{
		/*	if transition is valid, that's what we want, return	*/
		if (is_valid_transition(traj, &a, &b))
			return;

		/*	otherwise, if accelerating	*/
		if (b.v >= a.v)
		{
			/*	Change Pi.v and save it	*/
			b.v = get_max_possible_vb(traj, &a, &b);
			Trajectory_voidSetPointAt(traj, i, &b);

			/*	no need to optimize speed of previous points	*/
			return;
		}

		/*	otherwise, if decelerating	*/
		/*	Change P(i-1).v and save it	*/
		a.v = get_max_possible_va(traj, &a, &b);
		Trajectory_voidSetPointAt(traj, i - 1, &a);

		/*	decrement i and update a, b, c	*/
		i--;
		Trajectory_voidGetPointAt(traj, i - 1, &a);
		Trajectory_voidGetPointAt(traj, i    , &b);
		Trajectory_voidGetPointAt(traj, i + 1, &c);
	}
}

/*******************************************************************************
 * Interface functions:
 ******************************************************************************/
void Trajectory_voidGetPointAt(Trajectory_t* traj, u32 index, Trajectory_Point_t* p)
{
	/*	if "index" is out of range:	*/
	if (index >= traj->numberOfPoints)
	{
		p->x = 0;
		p->y = 0;
		p->z = 0;
		p->v = 0;
		return;
	}

	/*	Otherwise, read point from SD-card	*/
	SDC_voidKeepTryingReadStream(
		&(traj->stream),
		index * sizeof(Trajectory_Point_t),
		(u8*)p,
		sizeof(Trajectory_Point_t));
}

void Trajectory_voidSetPointAt(Trajectory_t* traj, u32 index, Trajectory_Point_t* p)
{
	/*	if "index" is out of range:	*/
	if (index >= traj->numberOfPoints)
		return;

	/*	Otherwise, write point to SD-card	*/
	SDC_voidKeepTryingWriteStream(
		&(traj->stream),
		index * sizeof(Trajectory_Point_t),
		(u8*)p,
		sizeof(Trajectory_Point_t));
}

void Trajectory_voidReset(Trajectory_t* traj, Trajectory_Point_t* pFirst)
{
	traj->numberOfPoints = 0;
	SDC_voidResetLineReader(&(traj->stream));
	Trajectory_voidAddPoint(traj, pFirst);
}

void Trajectory_voidAddPoint(Trajectory_t* traj, Trajectory_Point_t* p)
{
	traj->numberOfPoints++;
	Trajectory_voidSetPointAt(traj, traj->numberOfPoints - 1, p);
}

void Trajectory_voidPlan(Trajectory_t* traj)
{
	/*	if trajectory is empty (has no points), return	*/
	if (traj->numberOfPoints == 0)
		return;

	/*
	 * if trajectory has only 1 point, return.
	 * (as its speed is initially set before even calling this function)
	 */
	if (traj->numberOfPoints == 1)
		return;

	/*	calculate and optimize speeds of points from second to before last	*/
	for (u32 i = 1; i < traj->numberOfPoints - 1; i++)
	{
		calculate_and_optimize(traj, i);
	}

	/*	set last point speed to zero. TODO: optimize all previous points	*/
	Trajectory_Point_t p;
	Trajectory_voidGetPointAt(traj, traj->numberOfPoints - 1, &p);
	p.v = 0;
	Trajectory_voidSetPointAt(traj, traj->numberOfPoints - 1, &p);
}

void Trajectory_voidPrint(Trajectory_t* traj)
{
	Trajectory_Point_t p;

	for (u32 i = 0; i < traj->numberOfPoints; i++)
	{
		Trajectory_voidGetPointAt(traj, i, &p);
		trace_printf("P#%d: %d, %d, %d, %d\n", i, p.x, p.y, p.z, p.v);
	}
}



















