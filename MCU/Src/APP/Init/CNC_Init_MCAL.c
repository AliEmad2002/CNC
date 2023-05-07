/*
 * CNC_Init_MCAL.c
 *
 *  Created on: Feb 21, 2023
 *      Author: ali20
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "G_code_interface.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "CNC_UART_ISRs.h"
#include "CNC_Init_MCAL.h"



void CNC_voidInitMCAL(void)
{
	CNC_voidInitFPU();

	CNC_voidInitRCC();

	CNC_voidInitSysTick();

	CNC_voidInitUART();
}

void CNC_voidInitFPU(void)
{
	/*	only if the used target has one	*/
	#if TARGET_ID == STM32F401x
	FPU_voidEnable();
	#endif
}

void CNC_voidInitRCC(void)
{
	/**	Init system clock	**/
	RCC_voidSysClockInit();

	/**	Enable GPIO ports	**/
	/*	Things for STM32f1x only:	*/
	#if TARGET_ID == STM32F10x
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_AFIO);
	RCC_Bus_t gpioBus = RCC_Bus_APB2;

	/*	Things for STM32f401x only:	*/
	#elif TARGET_ID == STM32F401x
	RCC_Bus_t gpioBus = RCC_Bus_AHB1;
	#endif

	/*	Things for both	*/
	RCC_voidEnablePeripheralClk(gpioBus, RCC_PERIPHERAL_IOPA);
	RCC_voidEnablePeripheralClk(gpioBus, RCC_PERIPHERAL_IOPC);
	RCC_voidEnablePeripheralClk(gpioBus, RCC_PERIPHERAL_IOPB);
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_USART1);

	/**	Enable timers	**/
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_TIM1);
}

void CNC_voidInitUART(void)
{
	/*	init	*/
	UART_voidFastInit(UART_UNIT_NUMBER, UART_BAUD_RATE, UART_AFIO_MAP);

//	/*	enable UART receive interrupt	*/
//	NVIC_voidEnableInterrupt(UART_UNIT_NUMBER + NVIC_Interrupt_USART1);
//	UART_voidEnableInterrupt(UART_UNIT_NUMBER, UART_Interrupt_RXNE);
//	UART_voidSetCallBack(
//		UART_UNIT_NUMBER, UART_Interrupt_RXNE, CNC_voidRxCallBack);
}

void CNC_voidInitSysTick(void)
{
	/*	init	*/
	STK_voidInit();

	/*	enable	*/
	STK_voidEnableSysTick();

	/*	enable ovfCounter	*/
	STK_voidStartTickMeasure(STK_TickMeasureType_OverflowCount);
}


