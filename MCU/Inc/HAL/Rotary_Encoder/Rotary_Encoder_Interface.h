/*
 * Rotary_Encoder_Interface.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Ali Emad Ali
 *
 * Note: debouncing is user's responsibility, and may be implemented in counting
 * callbacks.
 */

#ifndef INCLUDE_HAL_ROTARY_ENCODER_ROTARY_ENCODER_INTERFACE_H_
#define INCLUDE_HAL_ROTARY_ENCODER_ROTARY_ENCODER_INTERFACE_H_


typedef struct{
	s32 count;
	u64 lastTimeStamp;

	GPIO_PortName_t outAPort;
	GPIO_PortName_t outBPort;

	u8 outAPin;
	u8 outBPin;

	u8 isEnabled;
}Rotary_Encoder_t;

/*	Note: Last 6 parameters must be initialized previously	*/
void Rotary_Encoder_voidInit(Rotary_Encoder_t* encoder);


#endif /* INCLUDE_HAL_ROTARY_ENCODER_ROTARY_ENCODER_INTERFACE_H_ */
