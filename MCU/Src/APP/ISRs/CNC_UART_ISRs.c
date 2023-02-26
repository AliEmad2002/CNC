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
#include "Queue_interface.h"
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
#include "CNC_UART_ISRs.h"

/*
 * Buffer that is temporarily holding the string being currently received,
 * until data passed passed to msg queue.
 */
static char currentRecvStr[UART_MAX_STRLEN];
static u32 currentRecvLen = 0;

extern Queue_t queue;

void CNC_voidRxCallBack(void)
{
	/**	Getting the just received byte	**/
	char byte;

	/*	read UART data register	*/
	(void)UART_enumReciveByte(UART_UNIT_NUMBER, &byte);

	/*	send ack	*/
	(void)UART_enumSendByte(UART_UNIT_NUMBER, UART_COMPUTER_ACK_BYTE);

	/**	If the received byte is not a terminator, just add it and return	**/
	if (byte != UART_COMPUTER_TERMINATOR_BYTE)
	{
		currentRecvStr[currentRecvLen++] = byte;

		return;
	}

	/**
	 * Otherwise, if the received byte is a terminator, parse "currentRecvStr"
	 * to a msg, and push it into the queue, and clear "currentRecvLen".
	 **/
	if (byte == UART_COMPUTER_TERMINATOR_BYTE)
	{
		/*	Convention termination of string	*/
		currentRecvStr[currentRecvLen] = '\0';

		/*	Reset byte counter	*/
		currentRecvLen = 0;

		/*	Parse received data into a "G_Code_Msg_t"	*/
		G_Code_Msg_t msg;

		b8 parseSuccess = G_Code_b8ParseLine(&msg, currentRecvStr);

		/*	if parsing failed	*/
		if (!parseSuccess)
		{
			/*	flush the UART receive buffer	*/
			UART_voidFlushDataReceiveRegister(UART_UNIT_NUMBER);

			/*	send request to receive corrupted data again	*/
			(void)UART_enumSendByte(
				UART_UNIT_NUMBER, UART_COMPUTER_RESEND_BYTE);

			/*	don't push corrupted data to queue	*/
			return;
		}

		/*	otherwise, add to message queue	*/
		b8 addedToQueueSuccess = Queue_b8Push(&queue, &msg);

		if (!addedToQueueSuccess)
		{
			/*	TODO: instead, pause receiving until an object is popped from queue	*/
			trace_printf("Queue full\n");
			while(1);
		}
	}
}
