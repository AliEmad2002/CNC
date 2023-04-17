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

/*	APP	*/
#include "CNC_config.h"
#include "CNC_interface.h"
#include "CNC_Init_MCAL.h"
#include "CNC_Init_HAL.h"


CNC_t CNC;
Queue_t queue;

int main(void)
{
	/*	init queue	*/
	#if ENABLE_QUEUE
		Queue_voidInit(&queue);
	#else
		trace_printf("Please enable Queue in \"Queue_Config.h\"!\n");
		trace_printf("Program Stopped\n");
		return -1;
	#endif

	/*	init MCAL	*/
	CNC_voidInitMCAL();

	/*	power stabilization delay	*/
	Delay_voidBlockingDelayMs(STARTUP_STABLIZATION_DELAY_MS);

	/*	init HAL	*/
	CNC_voidInitHAL();

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

	//CNC_voidProbe(&CNC);

	/*	Super-Loop	*/
	while(1)
	{
		/*	wait for queue counter to be at least one item	*/
		while(Queue_u16GetLenUsed(&queue) == 0);

		G_Code_Msg_t* msgPtr;	/*	no need for allocation, queue will do it	*/

		/*	pop first of the queue	*/
		Queue_b8Pop(&queue, &msgPtr);

		/*	execute the msg	*/
		CNC_voidExecute(&CNC, msgPtr);

		/*	free msgPtr	*/
		G_Code_voidFreeMsg(msgPtr);

		/*	send cmd completed ack	*/
		(void)UART_enumSendByte(UART_UnitNumber_1, '$');
	}
}








