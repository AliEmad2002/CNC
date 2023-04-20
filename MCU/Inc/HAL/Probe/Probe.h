/*
 * Probe.h
 *
 *  Created on: Apr 20, 2023
 *      Author: Ali Emad
 */

#ifndef INCLUDE_HAL_PROBE_PROBE_H_
#define INCLUDE_HAL_PROBE_PROBE_H_

typedef struct{
	u8 port             : 3;
	u8 pin              : 4;
	u8 openCirciutLevel : 1;
}Probe_t;

typedef enum{
	Probe_State_OpenCircuit,
	Probe_State_ClosedCircuit
}Probe_State_t;

void Probe_voidInit(Probe_t* probe);

u8 Probe_u8GetStatus(Probe_t* probe);	// 0: open circuit, 1: closed circuit.

#endif /* INCLUDE_HAL_PROBE_PROBE_H_ */
