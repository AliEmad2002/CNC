/*
 * CNC_UART_ISRs.c
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
#include <diag/trace.h>

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
#include "CNC_UART_ISRs.h"

extern CNC_t CNC;

void CNC_voidRxCallBack(void)
{
	/*	read UART data register	*/
	(void)UART_voidFlushDataReceiveRegister(UART_UNIT_NUMBER);

	/*	send current position	*/
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)( CNC.stepperArr[0].currentPos & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[0].currentPos >> 8) & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[0].currentPos >> 16) & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[0].currentPos >> 24) & 0xFF));

	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)( CNC.stepperArr[1].currentPos & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[1].currentPos >> 8) & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[1].currentPos >> 16) & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[1].currentPos >> 24) & 0xFF));

	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)( CNC.stepperArr[2].currentPos & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[2].currentPos >> 8) & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[2].currentPos >> 16) & 0xFF));
	(void)UART_enumSendByte(UART_UNIT_NUMBER, (u8)((CNC.stepperArr[2].currentPos >> 24) & 0xFF));
}
