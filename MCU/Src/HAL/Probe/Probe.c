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

u8 Probe_u8GetStatus(Probe_t* probe)	// 0: open circuit, 1: closed circuit.
{
	return GPIO_b8ReadPinDigital(probe->port, probe->pin) ^ probe->openCirciutLevel;
}
