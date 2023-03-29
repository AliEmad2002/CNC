/*
 * CNC_main.c
 *
 * Created: 		11 Jul 2022
 * Last modified:	20 Sep 2022
 * Author:			Ali Emad.
 * Under/For:		Assiut Robotics team.
 */

/*
 *												A C K N O W L E D G M E N T
 * Even though it may not be the best program among likes - hahaha - but during this project I've learned and gained
 * a quantity that I myself am compensated with, hoping it would improve my skills, looking forward for the best and
 * for never stopping the process of learning, trying, making mistakes, debugging, optimizing, and agile-ing over.
 *
 * Thanks to every single person helped me in this project, technically or emotionally, demonstrating principles,
 * sharing previous experiences, providing hardware material, or much more that I may not even remember.
 *	-	Family.						For their patience and taking over a lot off me.
 *	-	Assiut Robotics team.		For proving - nearly most of - hardware material and workspace.
 *	-	Ahmed Osama.				(technical demonstrator at electronics and communication department, faculty of
 *									 engineering, Assiut university). For his guidance, supervision, and most importantly:
 *									 encouragement.
 *	-	Eslam Wael.					(colleague student). Mechanical engineer.
 *	-	Mohammed Mahmoud Abdo.		(colleague student). For all the time we spent brainstorming and discussing methods.
 *	-	Tarek M. Medhat.			(colleague student). User interface designer.
 *	-	Ahmed Abdul-Baset.			(colleague student). PCB designer.
 *	-	Kareem Essam.				(SW engineer at Valeo Egypt). For sharing previous experiences in CNC machines.
 *	-	Mohammed G. Eleish.			(SW engineer at Valeo Egypt). For sharing previous experiences in MCU interfacing.
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

/*	HAL	*/
#include "Stepper_interface.h"

/*	APP	*/
#include "CNC_config.h"
#include "CNC_interface.h"
#include "CNC_Init_MCAL.h"
#include "CNC_Init_HAL.h"

CNC_t CNC;
Queue_t queue;

int main(void)
{
	/*	power stabilization delay	*/
	Delay_voidBlockingDelayMs(STARTUP_STABLIZATION_DELAY_MS);

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

	/*	init HAL	*/
	CNC_voidInitHAL();

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








