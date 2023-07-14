/*
 * Button_interface.h
 *
 *  Created on: Jul 14, 2023
 *      Author: ali20
 */

#ifndef HAL_BUTTON_BUTTON_INTERFACE_H_
#define HAL_BUTTON_BUTTON_INTERFACE_H_



typedef struct{
	u64 lastTimeStamp;

	GPIO_PortName_t outPort;
	u8 outPin;
	u8 isPressed;	// flag that is set by the module, and cleared by user.
	u32 msBouncingDelay;
}Button_t;

void Button_voidInit(Button_t* button);




#endif /* HAL_BUTTON_BUTTON_INTERFACE_H_ */
