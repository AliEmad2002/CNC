/*
 * Probe.c
 *
 *  Created on: Apr 20, 2023
 *      Author: Ali Emad
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"

/*	MCAL	*/
#include "GPIO_interface.h"

/*	SELF	*/
#include "Probe.h"

void Probe_voidInit(Probe_t* probe)
{
	if (probe->openCirciutLevel == 1)
		GPIO_voidSetPinInputPullUp(probe->port, probe->pin);
	else
		GPIO_voidSetPinInputPullDown(probe->port, probe->pin);
}

__attribute__((always_inline)) inline
u8 Probe_u8GetStatus(Probe_t* probe)	// 0: open circuit, 1: closed circuit.
{
	volatile u8 pinState = GPIO_DIGITAL_READ(probe->port, probe->pin);

	return pinState ^ probe->openCirciutLevel;
}
