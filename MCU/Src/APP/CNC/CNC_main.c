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
#include "Stack_interface.h"
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

char str[MAX_MSG_LEN];
u8 strLen;

void RX_ISR_callBack(void);

int main(void)
{
	/*	enable FPU	- if there's one -	*/
	#if TARGET_ID == STM32F401x
	FPU_voidEnable();
	#endif

	/*	init RCC	*/
	RCC_voidSysClockInit();

	/*	RCC enable peripherals	*/
	#if TARGET_ID == STM32F401x
	RCC_Bus_t gpioBus = RCC_Bus_AHB1;
	#elif TARGET_ID == STM32F10x
	RCC_Bus_t gpioBus = RCC_Bus_APB2;
	#endif

	/*	enable AFIO (STM32f10x only)	*/
	#if TARGET_ID == STM32F10x
	RCC_voidEnablePeripheralClk(gpioBus, RCC_PERIPHERAL_AFIO);
	#endif
	RCC_voidEnablePeripheralClk(gpioBus, RCC_PERIPHERAL_IOPA);
	RCC_voidEnablePeripheralClk(gpioBus, RCC_PERIPHERAL_IOPC);
	RCC_voidEnablePeripheralClk(gpioBus, RCC_PERIPHERAL_IOPB);
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_USART1);

	/*	init UART corresponding pins as AF pins	*/
	#if TARGET_ID == STM32F401x
	GPIO_voidSetPinMode(DIO_PORT_B, 6, GPIO_Mode_AF);
	GPIO_voidSetPinMode(DIO_PORT_B, 7, GPIO_Mode_AF);

	GPIO_voidSetAlternateFunction(DIO_PORT_B, 6, DIO_alternateFunction_USART1And2);
	GPIO_voidSetAlternateFunction(DIO_PORT_B, 7, DIO_alternateFunction_USART1And2);
	#elif TARGET_ID == STM32F10x
	GPIO_voidSetPinMode(GPIO_PortName_B, 6, GPIO_Mode_AF_PushPull);
	GPIO_voidSetPinOutputSpeed(GPIO_PortName_B, 6, GPIO_OutputSpeed_10MHz);
	GPIO_voidSetPinMode(GPIO_PortName_B, 7, GPIO_Mode_AF_PushPull);
	GPIO_voidSetPinOutputSpeed(GPIO_PortName_B, 7, GPIO_OutputSpeed_Null);
	AFIO_voidRemap(AFIO_Peripheral_USART1, AFIO_Usart1_Map_TxB6_RxB7);
	#endif

	/*	power stabilization delay	*/
	Delay_voidBlockingDelayMs(STARTUP_STABLIZATION_DELAY_MS);

	/*	init stack	*/
	Stack_voidInit();
	strLen = 0;

	/*	init UART	*/
	UART_voidFastInit(UART_UnitNumber_1, BAUD_RATE);

	/*	enable UART receive interrupt	*/
	NVIC_voidEnableInterrupt(NVIC_Interrupt_USART1);
	UART_voidEnableInterrupt(UART_UnitNumber_1, UART_Interrupt_RXNE);
	UART_voidSetCallBack(UART_UnitNumber_1, UART_Interrupt_RXNE, RX_ISR_callBack);

	/*	init sysTick	*/
	STK_voidInit(STK_ClockSource_AHB_by8, 0);
	STK_voidEnableSysTick();
	STK_voidStartTickMeasure(STK_TickMeasureType_OverflowCount);
	
	/*	init stepper motors	*/
	Stepper_t* stepperArr = (Stepper_t*)malloc(3 * sizeof(Stepper_t));
	
	Stepper_voidInit(stepperArr + X, X_STEP_PIN, X_DIR_PIN);
	Stepper_voidInit(stepperArr + Y, Y_STEP_PIN, Y_DIR_PIN);
	Stepper_voidInit(stepperArr + Z, Z_STEP_PIN, Z_DIR_PIN);
	
	/*	init CNC	*/
	CNC_t CNC;
	CNC_voidInit(&CNC, AUTO_LEVELING_PROBE_PIN, stepperArr);

	while(1)
	{
		/*	wait for stack counter to be at least one item	*/
		while(Stack_u16GetCount() == 0);
		
		G_Code_Msg_t* msgPtr;	/*	no need for allocation, stack will do it	*/

		/*	pop first of the stack	*/
		Stack_ptrPop((void**)&msgPtr);

		/*	execute the msg	*/
		CNC_voidExecute(&CNC, msgPtr);

		/*	free msgPtr	*/
		G_Code_voidFreeMsg(&msgPtr);

		/*	send cmd completed ack	*/
		(void)UART_enumSendByte(UART_UnitNumber_1, '$');
	}
}

void RX_ISR_callBack(void)
{
	char byte;

	/*	receive byte from computer	*/
	(void)UART_enumReciveByte(UART_UnitNumber_1, &byte);

	/*	send ack	*/
	(void)UART_enumSendByte(UART_UnitNumber_1, ';');

	/*
	 * if the received byte is a terminator, parse "str" to a msg,
	 * and push it into the stack, and clear "strLen".
	 */
	if (byte == ';')
	{
		str[strLen] = '\0';
		G_Code_Msg_t msg;
		G_Code_voidParseLine(&msg, str);
		Stack_voidPush(&msg);
		strLen = 0;
	}

	/*	else add it to "str"	*/
	else
	{
		str[strLen++] = byte;
	}
}






