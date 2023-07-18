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
#include "SCB_interface.h"
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
#include "CNC_Init_MCAL.h"



void CNC_voidInitMCAL(void)
{
	CNC_voidInitFPU();

	CNC_voidInitRCC();

	CNC_voidInitNVIC();

	CNC_voidInitSysTick();

	CNC_voidInitUART();
}

void CNC_voidInitFPU(void)
{
	/*	only if the used target has one	*/
}

void CNC_voidInitRCC(void)
{
	/**	Init system clock	**/
	RCC_voidSysClockInit();

	/**	Enable GPIO ports	**/
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_AFIO);
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_IOPA);
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_IOPC);
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_IOPB);

	/**	Enable UART	**/
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_USART1);

	/**	Enable SPI	**/
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_SPI1);

	/**	Enable EXTI	**/
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_EXTI);

	/**	Enable timers	**/
	RCC_voidEnablePeripheralClk(RCC_Bus_APB2, RCC_PERIPHERAL_TIM1);
}

void CNC_voidInitUART(void)
{

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

void CNC_voidInitNVIC(void)
{
	SCB_voidSetPriorityGroupsAndSubGroupsNumber(SCB_PRIGROUP_group4_sub4);

	/*	SysTick is of highest priority	*/
	NVIC_voidSetInterruptPriority(NVIC_Interrupt_Systick, 0, 0);

	/*	Limit switches are of normal priorities	*/
	NVIC_voidSetInterruptPriority(EXTI_u8FindVector(X_LIM_PIN%16), 1, 0);
	NVIC_voidSetInterruptPriority(EXTI_u8FindVector(Y_LIM_PIN%16), 1, 0);
	NVIC_voidSetInterruptPriority(EXTI_u8FindVector(Z_LIM_PIN%16), 1, 0);

	/*	UART is of lowest priority	*/
	NVIC_voidSetInterruptPriority(NVIC_Interrupt_USART1, 2, 0);
	NVIC_voidSetInterruptPriority(NVIC_Interrupt_USART2, 2, 0);
}
