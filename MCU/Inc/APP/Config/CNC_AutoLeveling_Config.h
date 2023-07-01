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
#define MAX_PROBE_STEPS						(30 * STEPS_PER_MM)		// 30mm

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
#define AL_SLOW_SPEED_TICKS_PER_STEP		(4000)
#define AL_FAST_SPEED_TICKS_PER_STEP		(3200)

#define AUTO_LEVELING_FLASH_BASE_PAGE		55

/*
 * Probing modes: (un-comment the mode to be used only)
 */
/*	Probes using one measure only	*/
//#define AUTO_LEVELING_PROBING_MODE_ONE_ONLY

/*
 * Probes using one fast measure at first, then going up for small distance and
 * making another measure slowly. The second measure is the one actually taken
 */
#define AUTO_LEVELING_PROBING_MODE_ONE_FAST_ONE_SLOW
#define AUTO_LEVELING_PROBING_SMALL_DISTANCE		(80*3) // 80*5 step = 0.5mm


#endif /* INCLUDE_APP_CONFIG_CNC_AUTOLEVELING_CONFIG_H_ */
