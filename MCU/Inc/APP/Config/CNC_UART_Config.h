/*
 * CNC_UART_Config.h
 *
 *  Created on: Feb 21, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_CONFIG_CNC_UART_CONFIG_H_
#define INCLUDE_APP_CONFIG_CNC_UART_CONFIG_H_


/******************************************************************************
 * 	HW configuration:
 ******************************************************************************/
#define UART_UNIT_NUMBER				UART_UnitNumber_1

#define UART_AFIO_MAP					0

#define UART_BAUD_RATE					115200

/******************************************************************************
 * 	Buffer configuration:
 ******************************************************************************/
#define UART_MAX_STRLEN						128	// bytes

#define LOOK_AHEAD_STACK_LEN				64	//	messages

/******************************************************************************
 * 	Computer handshake:
 ******************************************************************************/
#define UART_COMPUTER_ACK_BYTE			';'

#define UART_COMPUTER_TERMINATOR_BYTE	';'

#define UART_COMPUTER_RESEND_BYTE		'+'



#endif /* INCLUDE_APP_CONFIG_CNC_UART_CONFIG_H_ */
