/*
 * Rotary_Encoder_Program.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Ali Emad Ali
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Delay_interface.h"

/*	MCAL	*/
#include "GPIO_interface.h"
#include "EXTI_interface.h"
#include "STK_interface.h"

/*	SELF	*/
#include "Rotary_Encoder_Interface.h"

static void Rotary_Encoder_voidACallback(void* encoderPtr)
{
	Rotary_Encoder_t* encoder = (Rotary_Encoder_t*)encoderPtr;

	if (!encoder->isEnabled)
		return;

	/*	if time since last timestamp less than 10ms, return	*/
	volatile u64 currentTimestamp = STK_u64GetElapsedTicks();
	volatile u64 deltaTime = currentTimestamp - encoder->lastTimeStamp;
	encoder->lastTimeStamp = currentTimestamp;
	if (deltaTime < 10 * STK_TICKS_PER_MS)
		return;

	/*	read B level	*/
	volatile b8 bLevel = GPIO_DIGITAL_READ(encoder->outBPort, encoder->outBPin);

	/*	if B level is low ==> CCW	*/
	if (bLevel == 0)
	{
		encoder->count--;
	}

	/*	otherwise ==> CW	*/
	else
	{
		encoder->count++;
	}

	EXTI_CLEAR_FLAG(encoder->outBPin);
}

void Rotary_Encoder_voidInit(Rotary_Encoder_t* encoder)
{
	/*	reset counter	*/
	encoder->count = 0;

	/*	reset timestamp	*/
	encoder->lastTimeStamp = 0;

	/*	init pins as pulled up inputs	*/
	GPIO_voidSetPinInputPullUp(encoder->outAPort, encoder->outAPin);
	GPIO_voidSetPinInputPullUp(encoder->outBPort, encoder->outBPin);

	/*	init EXTI of pinA	*/
	EXTI_voidEnableLine(			encoder->outAPin);
	EXTI_voidMapLine(				encoder->outAPin, encoder->outAPort);
	EXTI_voidSetCallBack(			encoder->outAPin, Rotary_Encoder_voidACallback, encoder);
	EXTI_voidSetTriggeringEdge(		encoder->outAPin, EXTI_Trigger_risingEdge);
	EXTI_voidEnableLineInterrupt(	encoder->outAPin);
}










