/*
 * CNC_Steppers_Config.h
 *
 *  Created on: Feb 21, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_CONFIG_CNC_STEPPERS_CONFIG_H_
#define INCLUDE_APP_CONFIG_CNC_STEPPERS_CONFIG_H_


/*	stepper motor drivers' pins (slave in our poor pathetic case)	*/
#define X_STEP_PIN							GPIO_Pin_A5
#define X_DIR_PIN							GPIO_Pin_A6

#define Y_STEP_PIN							GPIO_Pin_A3
#define Y_DIR_PIN							GPIO_Pin_A4

#define Z_STEP_PIN							GPIO_Pin_A1
#define Z_DIR_PIN							GPIO_Pin_A2

/*	How frequently will speed be changed, in steps	*/
#define SPEED_CHANGE_DELTA		 			64

/*	steps per mm	*/
#define STEPS_PER_MM						1600

/*	ratio between maximum rapid speed to maximum feed speed	*/
#define RAPID_SPEED_MAX_TO_FEED_SPEED_MAX	10

/*	minimum operating speed	*/
#define SPEED_MIN							STEPS_PER_MM




#endif /* INCLUDE_APP_CONFIG_CNC_STEPPERS_CONFIG_H_ */
