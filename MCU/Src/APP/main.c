/*
 * CNC_main.c
 *
 * Created: 		11 Jul 2022
 * Last modified:	20 Sep 2022
 * Author:			Ali Emad.
 *
 * Under/For:
 * 	-	Previously: Assiut Robotics team.
 * 	-	Currently:  IOT lab, electrical engineering department, Assiut university.
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Delay_interface.h"
#include <string.h>

/*	APP	*/
#include "CNC_config.h"
#include "CNC_interface.h"
#include "CNC_Init_MCAL.h"

#if SIMULATION_ON
#include "UART_interface.h"
#include <diag/trace.h>
#endif

CNC_t CNC;

int main(void)
{
	/*	init MCAL	*/
	CNC_voidInitMCAL();

	/*	power stabilization and MCAL ready delay	*/
	Delay_voidBlockingDelayMs(STARTUP_STABLIZATION_DELAY_MS);

	/*	init CNC object	*/
	CNC_voidInit(&CNC);

#if !SIMULATION_ON
	char fileNameStr[5];
	strcpy(fileNameStr, "0.NC");
	volatile u8 fileCount = 0;
	while(1)
	{
		/*	Open G-code file	*/
		SDC_voidKeepTryingOpenStream(&(CNC.gcodeFile), &(CNC.sdCard), fileNameStr);

		/*	Make manual movement	*/
		CNC_voidMoveManual(&CNC);

		/*	Change RAM stored position	*/
		CNC_voidChangeRamPos(&CNC);

		/*	Run G-code file from the SD-card	*/
		CNC_voidRunGcodeFile(&CNC);

		/*	Ask user if they want to do a new operation	*/
		if (CNC_u8AskNew(&CNC))
		{
			fileCount++;
			fileNameStr[0] = '0' + fileCount;
		}
		else
			break;
	}
#else
	SDC_voidKeepTryingOpenStream(&(CNC.gcodeFile), &(CNC.sdCard), "0.NC");

	/*	wait for the first MATLAB request to start simulation	*/
	while(!UART_b8GetRxFlag(UART_UNIT_NUMBER));

	/*	Run G-code file from the SD-card	*/
	CNC_voidRunGcodeFile(&CNC);
	trace_printf("Done!\n");
#endif

	while(1);
}
