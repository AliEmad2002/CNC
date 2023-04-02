/*
 * DC_Motor_Interface.h
 *
 * An open-loop, single direction motor controller. (Based on single transistor)
 *
 *  Created on: Apr 2, 2023
 *      Author: Ali Emad Ali
 */

#ifndef INCLUDE_HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_
#define INCLUDE_HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_


typedef struct{
	u8 timerUnitNumber;
	TIM_Channel_t channelNumber;
}DC_Motor_t;


void DC_Motor_voidInit(
	DC_Motor_t* motor, u8 timerUnitNumber, TIM_Channel_t channelNumber, u8 afioMap);

/*
 * Speed is a value between 0 and 2^16 - 1.
 */
void DC_Motor_voidSetSpeed(DC_Motor_t* motor, u16 speed);


#endif /* INCLUDE_HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_ */
