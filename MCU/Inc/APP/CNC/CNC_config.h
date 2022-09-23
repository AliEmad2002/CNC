/*
 * CNC_config.h
 *
 * Created: 8/11/2022 8:33:42 PM
 *
 * Copyright (c) 2022, Ali Emad
 * All rights reserved.
 *
 * This source code is licensed under the GPL-style license found in the
 * LICENSE file in the root directory of this source tree. 
 */ 


#ifndef CNC_CONFIG_H_
#define CNC_CONFIG_H_

/*	UART baud rate (to communicate with PC (if used))	*/
#define BAUD_RATE					9600

/*	stepper motor drivers' pins (slave in our poor pathetic case)	*/
#define X_STEP_PIN							DIO_PIN_A4
#define X_DIR_PIN							DIO_PIN_A5

#define Y_STEP_PIN							DIO_PIN_A2
#define Y_DIR_PIN							DIO_PIN_A3

#define Z_STEP_PIN							DIO_PIN_A0
#define Z_DIR_PIN							DIO_PIN_A1

/*	auto leveling probe pin	*/
#define AUTO_LEVELING_PROBE_PIN				DIO_PIN_A7

/*	how frequently will speed be changed	*/
#define SPEED_CHANGE_DELTA		 			64

/*	safety parameter to avoid miss contact machine self-destruction	*/
#define MAX_PROBE_STEPS						8000		// 5mm

/*	steps per mm	*/
#define STEPS_PER_MM						1600

/*	enough air Z-axis distance between bit and material while scanning depth map	*/
#define AUTO_LEVELING_UP					1600	// 1mm

/*
 * enough air Z-axis distance between bit and material after scanning depth map
 * (must be valid and safe along the whole map @ AL disabled)
 */
#define AUTO_LEVELING_UP_MAX				1600*10	// 10mm

/*	ratio between maximum rapid speed to maximum feed speed	*/
#define RAPID_SPEED_MAX_TO_FEED_SPEED_MAX	10

/*	how much will dx, dy be trimmed	*/
#define AL_GRID_TRIMMER						20

/*	let other modules - i.e.: LCD, take their breath	*/
#define STARTUP_STABLIZATION_DELAY_MS		500

/*	max number of chars to be stored in one msg	*/
#define MAX_MSG_LEN							128

/*	probing speed inverse	*/
#define AL_SLOW_SPEED_TICKS_PER_STEP		1600

/*	minimum operating speed	*/
#define SPEED_MIN							1600

/*	*/
#define LOOK_AHEAD_STACK_LEN				64		// msg
#endif /* CNC_CONFIG_H_ */
