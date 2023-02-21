/*
 * UART_config.h
 *
 *  Created on: Oct 14, 2022
 *      Author: Ali Emad Ali
 */

#ifndef INCLUDE_MCAL_UART_UART_CONFIG_H_
#define INCLUDE_MCAL_UART_UART_CONFIG_H_

#define UART_NON_VALID_ECHO_ERR_CODE	0

#define UART_NON_VALID_ECHO_HANDLER		\
	ErrorHandler_voidExecute(UART_NON_VALID_ECHO_ERR_CODE)



#endif /* INCLUDE_MCAL_UART_UART_CONFIG_H_ */
