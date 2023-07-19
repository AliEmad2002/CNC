/*
 * CNC_Limit_Switches_Config.h
 *
 *  Created on: Jul 18, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_CONFIG_CNC_LIMIT_SWITCHES_CONFIG_H_
#define INCLUDE_APP_CONFIG_CNC_LIMIT_SWITCHES_CONFIG_H_


#define	X_LIM_PIN						GPIO_Pin_A4
#define	Y_LIM_PIN						GPIO_Pin_A3
#define	Z_LIM_PIN						GPIO_Pin_A2

#define LIM_SW_TICKS_BETWEEN_STEPS		(3200 * (72 / 8))

#define LIM_SW_RELEASE_DISTANCE			(800 * 10)	//10mm


#endif /* INCLUDE_APP_CONFIG_CNC_LIMIT_SWITCHES_CONFIG_H_ */
