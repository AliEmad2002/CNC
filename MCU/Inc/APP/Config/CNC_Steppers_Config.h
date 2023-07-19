/*
 * CNC_Steppers_Config.h
 *
 *  Created on: Feb 21, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_CONFIG_CNC_STEPPERS_CONFIG_H_
#define INCLUDE_APP_CONFIG_CNC_STEPPERS_CONFIG_H_


/*	stepper motor drivers' pins (slave in our poor pathetic case)	*/

#define X_DIR_PIN							GPIO_Pin_B3
#define X_STEP_PIN							GPIO_Pin_B4
#define X_EN_PIN							GPIO_Pin_B5

#define Y_DIR_PIN							GPIO_Pin_A0
#define Y_STEP_PIN							GPIO_Pin_A1
#define Y_EN_PIN							GPIO_Pin_A8

#define Z_DIR_PIN							GPIO_Pin_A9
#define Z_STEP_PIN							GPIO_Pin_A8
#define Z_EN_PIN							GPIO_Pin_A10

/*	spindles driving PWM signal	*/
#define SPINDLE_PWM_TIM_UNIT_NUMBER			4
#define SPINDLE_PWM_TIM_CHANNEL				TIM_Channel_1
#define SPINDLE_PWM_AFIO_MAP				0

/*	How frequently will speed be changed, in steps	*/
#define SPEED_CHANGE_DELTA		 			64

/*	steps per mm (initial, and could be changed by g-code later)	*/
#define STEPS_PER_MM						800

/*	minimum operating speed	*/
#define SPEED_MIN							(STEPS_PER_MM/4) // 0.25mm/sec




#endif /* INCLUDE_APP_CONFIG_CNC_STEPPERS_CONFIG_H_ */
