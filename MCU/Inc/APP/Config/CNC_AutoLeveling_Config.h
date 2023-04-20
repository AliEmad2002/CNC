/*
 * CNC_AutoLeveling_Config.h
 *
 *  Created on: Feb 21, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_CONFIG_CNC_AUTOLEVELING_CONFIG_H_
#define INCLUDE_APP_CONFIG_CNC_AUTOLEVELING_CONFIG_H_

/*	Probe pin	*/
#define AUTO_LEVELING_PROBE_PIN				GPIO_Pin_A8

#define AUTO_LEVELING_PROBE_OC_LEVEL		1

/*
 * Safety parameter to avoid miss contact machine self-destruction. (in steps)
 */
#define MAX_PROBE_STEPS						(10 * STEPS_PER_MM)		// 5mm

/*
 * Enough air Z-axis distance between bit and material while scanning depth map
 */
#define AUTO_LEVELING_UP					(1 * STEPS_PER_MM)		// 1mm

/*
 * enough air Z-axis distance between bit and material after scanning depth map
 * (must be valid and safe along the whole map @ AL disabled)
 */
#define AUTO_LEVELING_UP_MAX				(10 * STEPS_PER_MM)		// 10mm

/*	how much will dx, dy be trimmed	*/
#define AL_GRID_TRIMMER						20

/*	probing speed inverse	*/
#define AL_SLOW_SPEED_TICKS_PER_STEP		1600*25

#define AUTO_LEVELING_FLASH_BASE_PAGE		55


#endif /* INCLUDE_APP_CONFIG_CNC_AUTOLEVELING_CONFIG_H_ */
