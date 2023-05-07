/*
 * CNC_main.c
 *
 * Created: 		11 Jul 2022
 * Last modified:	20 Sep 2022
 * Author:			Ali Emad.
 *
 * Under/For:
 * 	-	Previously: Assiut Robotics team.
 * 	-	Currently:  IOT lab, electrical engineering department, Assiut university.
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Delay_interface.h"

/*	APP	*/
#include "CNC_config.h"
#include "CNC_interface.h"
#include "CNC_Init_MCAL.h"

//void steppers_test(void);

CNC_t CNC;

int main(void)
{
	/*	init MCAL	*/
	CNC_voidInitMCAL();

	/*	power stabilization and MCAL ready delay	*/
	Delay_voidBlockingDelayMs(STARTUP_STABLIZATION_DELAY_MS);

	/*	init CNC object	*/
	CNC_voidInit(&CNC);

	while(1)
	{
		/*	Make manual movement	*/
		CNC_voidMoveManual(&CNC);

		/*	Change RAM stored position	*/
		CNC_voidChangeRamPos(&CNC);

		/*	Run G-code file from the SD-card	*/
		CNC_voidRunGcodeFile(&CNC);

		/*	Ask user if they want to do a new operation	*/
		if (CNC_u8AskNew(&CNC))
			continue;
		else
			break;
	}

	while(1);
}

//void steppers_test(void)
//{
//	volatile u8 x = 0;
//	volatile u8 y = 0;
//	volatile u8 z = 0;
//	volatile u8 dirX = 0;
//	volatile u8 dirY = 0;
//	volatile u8 dirZ = 0;
//	volatile u32 delay = 1;
//	while (1)
//	{
//		if (x)
//			Stepper_voidStep(CNC.stepperArr, dirX, STK_u64GetElapsedTicks());
//		if (y)
//			Stepper_voidStep(CNC.stepperArr+1, dirY, STK_u64GetElapsedTicks());
//		if (z)
//			Stepper_voidStep(CNC.stepperArr+2, dirZ, STK_u64GetElapsedTicks());
//		Delay_voidBlockingDelayMs(delay);
//	}
//}
