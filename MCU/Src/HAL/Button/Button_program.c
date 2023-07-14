/*
 * Button_program.c
 *
 *  Created on: Jul 14, 2023
 *      Author: ali20
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"

/*	MCAL	*/
#include "GPIO_interface.h"
#include "EXTI_interface.h"
#include "STK_interface.h"

/*	SELF	*/
#include "Button_interface.h"

static void Button_voidCallback(void* buttonPtr)
{
	Button_t* button = (Button_t*)buttonPtr;

	/*	if time since last timestamp less than msBouncingDelay, return	*/
	volatile u64 currentTimestamp = STK_u64GetElapsedTicks();
	volatile u64 deltaTime = currentTimestamp - button->lastTimeStamp;
	button->lastTimeStamp = currentTimestamp;
	if (deltaTime < button->msBouncingDelay * STK_TICKS_PER_MS)
		return;

	/*	otherwise, raise pressed flag	*/
	button->isPressed = 1;
}

void Button_voidInit(Button_t* button)
{
	button->isPressed = 0;

	/*	init pin as pulled up input	*/
	GPIO_voidSetPinInputPullUp(button->outPort, button->outPin);

	/*	init EXTI of pin	*/
	EXTI_voidEnableLine(			button->outPin);
	EXTI_voidMapLine(				button->outPin, button->outPort);
	EXTI_voidSetCallBack(			button->outPin, Button_voidCallback, button);
	EXTI_voidSetTriggeringEdge(		button->outPin, EXTI_Trigger_fallingEdge);
	EXTI_voidEnableLineInterrupt(	button->outPin);
}
