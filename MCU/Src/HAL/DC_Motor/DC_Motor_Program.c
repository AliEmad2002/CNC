/*
 * DC_Motor_Program.c
 *
 *  Created on: Apr 2, 2023
 *      Author: Ali Emad Ali
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"

/*	MCAL	*/
#include "RCC_interface.h"
#include "TIM_interface.h"

/*	SELF	*/
#include "DC_Motor_Interface.h"

void DC_Motor_voidInit(
	DC_Motor_t* motor, u8 timerUnitNumber, TIM_Channel_t channelNumber, u8 afioMap)
{
	motor->channelNumber = channelNumber;
	motor->timerUnitNumber = timerUnitNumber;

	TIM_u64InitPWM(
		timerUnitNumber, channelNumber, TIM_OutputCompareMode_PWM2, 50 * 1000);

	TIM_voidInitOutputPin(timerUnitNumber, channelNumber, afioMap);

	TIM_voidEnableCounter(timerUnitNumber);
}

ALWAYS_INLINE void DC_Motor_voidSetSpeed(DC_Motor_t* motor, u16 speed)
{
	TIM_voidSetDutyCycle(motor->timerUnitNumber, motor->channelNumber, speed);
}







