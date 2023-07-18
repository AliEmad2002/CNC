/*
 * Limit_Switch_program.c
 *
 *  Created on: Jul 18, 2023
 *      Author: Ali Emad
 */


/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"

/*	MCAL	*/
#include "GPIO_interface.h"
#include "EXTI_interface.h"

/*	SELF	*/
#include "Limit_Switch_interface.h"

void LimitSwitch_voidInit(LimitSwitch_t* sw, void(*callback)(void*))
{
	EXTI_voidEnableLine(sw->pin);
	EXTI_voidMapLine(sw->pin, sw->port);
	EXTI_voidSetCallBack(sw->pin, callback, sw);

	if (sw->openCirciutLevel == 1)
	{
		GPIO_voidSetPinInputPullUp(sw->port, sw->pin);
		EXTI_voidSetTriggeringEdge(sw->pin, EXTI_Trigger_fallingEdge);
	}
	else
	{
		GPIO_voidSetPinInputPullDown(sw->port, sw->pin);
		EXTI_voidSetTriggeringEdge(sw->pin, EXTI_Trigger_risingEdge);
	}

	/*	Interrupt is initially enabled	*/
	LimitSwitch_voidEnableInterrupt(sw);
}

__attribute__((always_inline)) inline
void LimitSwitch_voidEnableInterrupt(LimitSwitch_t* sw)
{
	EXTI_voidEnableLineInterrupt(sw->pin);
}

__attribute__((always_inline)) inline
void LimitSwitch_voidDisableInterrupt(LimitSwitch_t* sw)
{
	EXTI_voidDisableLineInterrupt(sw->pin);
}

__attribute__((always_inline)) inline
u8 LimitSwitch_u8GetStatus(LimitSwitch_t* sw)
{
	volatile u8 pinState = GPIO_DIGITAL_READ(sw->port, sw->pin);

	return pinState ^ sw->openCirciutLevel;
}

