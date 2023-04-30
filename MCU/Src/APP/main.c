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
#include "Bit_Math.h"
#include "G_code_interface.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue_interface.h"
#include "Delay_interface.h"
#include "Target_config.h"

/*	MCAL	*/
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "FPU_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "FPEC_interface.h"
#include "TIM_interface.h"

/*	HAL	*/
#include "Stepper_interface.h"
#include "DC_Motor_Interface.h"
#include "SDC_interface.h"

/*	APP	*/
#include "CNC_config.h"
#include "CNC_interface.h"
#include "CNC_Init_MCAL.h"

#include "SDC_Private.h"

void steppers_test(void);

static s32 mapArr[400];
CNC_t CNC;

static u8 flagArr[1280] = {0};

u8 all_flags_set()
{
	for (u16 i = 0; i < 1280; i++)
	{
		if (flagArr[i] != 0xFF)
			return 0;
	}
	return 1;
}

ALWAYS_INLINE_STATIC u8 get_flag(u32 offset)
{
	return GET_BIT(flagArr[offset / 8], offset % 8);
}

ALWAYS_INLINE_STATIC u8 set_flag(u32 offset)
{
	return SET_BIT(flagArr[offset / 8], offset % 8);
}

u32 get_rand_unused_offset()
{
//	static u32 i = 0;
//	return i++;
	while(1)
	{
		u32 offset = ((u32)rand()) % 10240u;
		if (get_flag(offset) == 0)
			return offset;
	}
}

u32 numberOfFails = 0;
u32 numberOfHS = 0;

int main(void)
{
	/*	init MCAL	*/
	CNC_voidInitMCAL();

	//Delay_voidBlockingDelayMs(5000);

	srand(0);

	SDC_t sd;
	SDC_voidKeepTryingInitConnection(&sd, 1, SPI_UnitNumber_1, SD_CS_PIN, SD_RST_PIN, SD_AFIO_MAP);
	SDC_voidKeepTryingInitPartition(&sd);

	SD_Stream_t s0, s1;
	SDC_voidKeepTryingOpenStream(&s0, &sd, "S0.BIN");
	SDC_voidKeepTryingOpenStream(&s1, &sd, "S1.BIN");

	u8 byte;
	u32 offset;
	u32 doneCount = 0;

	while(!all_flags_set())
	{
		offset = get_rand_unused_offset();

		SDC_voidKeepTryingReadStream(&s0, offset, &byte, 1);
		SDC_voidKeepTryingWriteStream(&s1, offset, &byte, 1);

		set_flag(offset);

		doneCount++;

		if (doneCount % 102 == 0)
		{
			static u32 i = 0;
			trace_printf("%d\n", i++);
		}
	}

	SDC_voidKeepTryingSaveStream(&s0);
	SDC_voidKeepTryingSaveStream(&s1);

	trace_printf("Program done!\n");
	trace_printf("numberOfFails = %d\n", numberOfFails);














//	/*	power stabilization and MCAL ready delay	*/
//	Delay_voidBlockingDelayMs(STARTUP_STABLIZATION_DELAY_MS);
//
//	/*	init CNC object	*/
//	CNC.map.mapArr = mapArr;
//	CNC_voidInit(&CNC);
//
//	while(1)
//	{
//		/*
//		 * Ask user if they want to do any prior to file operations.
//		 * For example:
//		 * 		-	level mapping.
//		 * 		-	setting parameters that not necessarily given in the G-code
//		 * 			file, like acceleration, maximum in-air (rapid) speed, etc...
//		 */
//		CNC_voidPriOperation(&CNC);
//
//		/*	Let user choose G-code file to run from the SD-card, and run it	*/
//		CNC_voidRunGcodeFile(&CNC);
//
//		/*	Ask user if they want to do a new operation	*/
//		if (CNC_u8AskNew(&CNC))
//			continue;
//		else
//			break;
//	}
//
//	while(1);
}

void steppers_test(void)
{
	volatile u8 x = 0;
	volatile u8 y = 0;
	volatile u8 z = 0;
	volatile u8 dirX = 0;
	volatile u8 dirY = 0;
	volatile u8 dirZ = 0;
	volatile u32 delay = 1;
	while (1)
	{
		if (x)
			Stepper_voidStep(CNC.stepperArr, dirX, STK_u64GetElapsedTicks());
		if (y)
			Stepper_voidStep(CNC.stepperArr+1, dirY, STK_u64GetElapsedTicks());
		if (z)
			Stepper_voidStep(CNC.stepperArr+2, dirZ, STK_u64GetElapsedTicks());
		Delay_voidBlockingDelayMs(delay);
	}
}
