/*
 * CNC_config.h
 *
 * Created: 8/11/2022 8:33:42 PM
 *  Author: Ali Emad Ali
 */ 


#ifndef CNC_CONFIG_H_
#define CNC_CONFIG_H_

#include "CNC_UART_Config.h"
#include "CNC_Steppers_Config.h"
#include "CNC_AutoLeveling_Config.h"

/*	error handler  (used in debugging)	*/
/*	here lib layer's default is used	*/
#define CNC_ERR_HANDLER(code)	ErrorHandler_voidExecute(code)

/*	let supply voltage levels stabilize along the system	*/
#define STARTUP_STABLIZATION_DELAY_MS		500

#endif /* CNC_CONFIG_H_ */
