/*
 * CNC_UI_Config.h
 *
 *  Created on: Jul 14, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_CONFIG_CNC_UI_CONFIG_H_
#define INCLUDE_APP_CONFIG_CNC_UI_CONFIG_H_

#define BUTTON_PIN							GPIO_Pin_B11
#define BUTTON_BOUNCING_DELAY_MS			100

#define ROTARY_A_PIN						GPIO_Pin_B1
#define ROTARY_B_PIN						GPIO_Pin_B10

#define TFT_SPI_UNIT_NUMBER					SPI_UnitNumber_2
#define TFT_SPI_AFIO_MAP					0
#define TFT_RST_PIN							GPIO_Pin_B12
#define TFT_A0_PIN							GPIO_Pin_B14
#define TFT_TIM_UNIT_NUMBER					1
#define TFT_TIM_CHANNEL_NUMBER				1
#define TFT_TIM_AFIO_MAP					0

#endif /* INCLUDE_APP_CONFIG_CNC_UI_CONFIG_H_ */
