/*
 * CNC_Init_HAL.c
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
#include "CNC_Init_HAL.h"
#include "CNC_interface.h"

static Stepper_t stepperArr[3];

/*	from main.c	*/
extern CNC_t CNC;

void CNC_voidInitHAL(void)
{
	/*	init steppers	*/
	CNC_voidInitSteppers();

	/*	init CNC object	*/
	CNC_voidInit(&CNC, AUTO_LEVELING_PROBE_PIN, stepperArr);
}

void CNC_voidInitSteppers(void)
{
	Stepper_voidInit(&stepperArr[X], X_STEP_PIN, X_DIR_PIN);
	Stepper_voidInit(&stepperArr[Y], Y_STEP_PIN, Y_DIR_PIN);
	Stepper_voidInit(&stepperArr[Z], Z_STEP_PIN, Z_DIR_PIN);
}







