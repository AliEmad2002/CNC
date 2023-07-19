/*
 * Limit_Switch_interface.h
 *
 *  Created on: Jul 18, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_HAL_LIMIT_SWITCH_LIMIT_SWITCH_INTERFACE_H_
#define INCLUDE_HAL_LIMIT_SWITCH_LIMIT_SWITCH_INTERFACE_H_

typedef struct{
	u8 port : 4;
	u8 pin : 4;

	u8 openCirciutLevel : 1;
}LimitSwitch_t;

void LimitSwitch_voidInit(LimitSwitch_t* sw, void(*callback)(void*), void* paramsPtr);

void LimitSwitch_voidEnableInterrupt(LimitSwitch_t* sw);

void LimitSwitch_voidDisableInterrupt(LimitSwitch_t* sw);

u8 LimitSwitch_u8GetStatus(LimitSwitch_t* sw);



#endif /* INCLUDE_HAL_LIMIT_SWITCH_LIMIT_SWITCH_INTERFACE_H_ */
