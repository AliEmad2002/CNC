///*
// * Trajectory.c
// *
// *  Created on: May 1, 2023
// *      Author: Ali Emad
// */
//
/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include <math.h>

/*	HAL	*/
#include "SDC_interface.h"

/*	SELF	*/
#include "Trajectory.h"
//
//
///*	returns sin(theta_b/2)	*/
//ALWAYS_INLINE_STATIC f32 get_sin_half_theta_b(Trajectory_Point_t* a, Trajectory_Point_t* b, Trajectory_Point_t* c)
//{
//	s32 xa = a->x;
//	s32 xb = b->x;
//	s32 xc = c->x;
//
//	s32 ya = a->y;
//	s32 yb = b->y;
//	s32 yc = c->y;
//
//	float m1 = (float)(ya - yb) / (float)(xa - xb);
//	float m2 = (float)(yb - yc) / (float)(xb - xc);
//
//	float tanTheta = fabs((m1 - m2) / (1.0f + m1*m2));
//
//	float cosTheta = sqrt(1.0f / (1.0f + tanTheta*tanTheta));
//
//	float sinHalfTheta = sqrt((1.0f - cosTheta) / 2.0f);
//	return sinHalfTheta;
//}
//
//static u32 get_vb(Trajectory_t* traj, Trajectory_Point_t* a, Trajectory_Point_t* b, Trajectory_Point_t* c)
//{
//	return (u32)(((f32)traj->vMax) * get_sin_half_theta_b(a, b, c));
//}
//
///*	returns magnitude of distance between two points	*/
//static u32 get_distance_between(Trajectory_Point_t* a, Trajectory_Point_t* b)
//{
//	s32 dx = a->x - b->x;
//	s32 dy = a->y - b->y;
//
//	u64 distSquared = (u64)dx * (u64)dx + (u64)dy * (u64)dy;
//	u32 dist = (u32)sqrt(distSquared);
//	return dist;
//}
//
///*
// * Checks if acceleration settings can change va to vb in the distance between
// * them.
// *
// * Returns 1 if valid. 0 otherwise.
// */
//static u8 is_valid_transition(Trajectory_t* traj, Trajectory_Point_t* a, Trajectory_Point_t* b)
//{
//	u32 x = get_distance_between(a, b);
//
//	u32 va = a->v;
//	u32 vb = b->v;
//
//	if (vb > va)
//	{
//		u64 vfSquared = (u64)va * (u64)va + 2ul * (u64)traj->accel * (u64)x;
//		if (vfSquared >= (u64)vb * (u64)vb)
//			return 1;
//		else
//			return 0;
//	}
//
//	else if (vb < va)
//	{
//		s64 vfSquared = (s64)va * (s64)va - 2 * (s64)traj->accel * (s64)x;
//		if (vfSquared <= (s64)vb * (s64)vb)
//			return 1;
//		else
//			return 0;
//	}
//
//	else
//		return 1;
//}
//
//static u32 get_max_possible_vb(Trajectory_t* traj, Trajectory_Point_t* a, Trajectory_Point_t* b)
//{
//	u32 x = get_distance_between(a, b);
//	u32 va = a->v;
//
//	u64 vmaxSquared = (u64)va * (u64)va + 2 * (u64)traj->accel * (u64)x;
//	u32 vmax = (u32)sqrt(vmaxSquared);
//	return vmax;
//}
//
//static u32 get_max_possible_va(Trajectory_Point_t* a, Trajectory_Point_t* b)
//{
//	return get_max_possible_vb(b, a);
//}
//
///*
// * flowchart of this function:
// * https://github.com/AliEmad2002/CNC/issues/7#issuecomment-1518841274
// */
//static void calculate_and_optimize(RFS_t* pRfs, u32 i)
//{
//	/*	extract points P(i-1), Pi and P(i+1) from the RFS	*/
//	Trajectory_Point_t a, b, c;
//	RFS_voidGetObject((u8*)&a, pRfs, i-1);
//	RFS_voidGetObject((u8*)&b, pRfs, i);
//	RFS_voidGetObject((u8*)&c, pRfs, i+1);
//
//	/*	TODO: optimize when to save	*/
//	/*	get vi	*/
//	b.v = get_vb(&a, &b, &c);
//	RFS_voidStoreObject((u8*)&b, pRfs, i);
//
//	while(i >= 1)
//	{
//		/*	if transition is valid, that's what we want, return	*/
//		if (is_valid_transition(&a, &b))
//			return;
//
//		/*	otherwise, if accelerating	*/
//		if (b.v >= a.v)
//		{
//			b.v = get_max_possible_vb(&a, &b);
//			RFS_voidStoreObject((u8*)&b, pRfs, i);
//			return;
//		}
//
//		/*	otherwise, if decelerating	*/
//		a.v = get_max_possible_va(&a, &b);
//		RFS_voidStoreObject((u8*)&a, pRfs, i-1);
//
//		/*	update	*/
//		i--;
//		RFS_voidGetObject((u8*)&a, pRfs, i-1);
//		RFS_voidGetObject((u8*)&b, pRfs, i);
//		RFS_voidGetObject((u8*)&c, pRfs, i+1);
//	}
//}
//
///*******************************************************************************
// * User interface functions:
// ******************************************************************************/
//void Trajectory_voidInit(Trajectory_t* traj, SDC_t* sdc, char* tempFileName)
//{
//	traj->numberOfPoints = 0;
//
//	/*	open stream	*/
//	SDC_voidKeepTryingOpenStream(&(traj->stream), sdc, tempFileName);
//}
//
//void Trajectory_voidSetVmax(Trajectory_t* traj, u32 v)
//{
//	traj->vMax = v;
//}
//
//void Trajectory_voidSetAcceleration(Trajectory_t* traj, u32 a)
//{
//	traj->accel = a;
//}
//
//void Trajectory_voidPlanTrajectory(Trajectory_t* traj)
//{
//	/*	if RFS is empty, return	*/
//	if (RFS_u8IndexExists(pRfs, 0) == 0)
//		return;
//
//	/*	set speed of the very first point zero	*/
//	Trajectory_Point_t point;
//	RFS_voidGetObject((u8*)&point, pRfs, 0);
//	point.v = 0;
//	RFS_voidStoreObject((u8*)&point, pRfs, 0);
//
//	/*	if RFS has only one point, return	*/
//	if (RFS_u8IndexExists(pRfs, 1) == 0)
//		return;
//
//	/*	calculate and optimize speeds of points from second to before last	*/
//	u32 i = 1;
//	while(RFS_u8IndexExists(pRfs, i+1))
//	{
//		calculate_and_optimize(pRfs, i);
//		i++;
//	}
//
//	/*	set last point speed to zero.	*/
//	/*	TODO: optimize other points based on it	*/
//	RFS_voidGetObject((u8*)&point, pRfs, i);
//	point.v = 0;
//	RFS_voidStoreObject((u8*)&point, pRfs, i);
//}
