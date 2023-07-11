/*
 * G_code_program.c
 *
 * Created: 7/13/2022 9:54:36 PM
 *  Author: Ali Emad
 */ 

/*	LIB	*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "My_Math.h"
#include "My_String.h"

/*	MCAL	*/
#include "UART_interface.h"

/*	self	*/
#include "G_code_interface.h"

#define ACCELFEED_INDEX		1
#define ACCELRAPID_INDEX	2

#include "CNC_interface.h"
extern CNC_t CNC;

void G_Code_voidCopyMsg(G_Code_Msg_t** copyPtrPtr, G_Code_Msg_t* originalPtr)
{
	/*	allocate the place in RAM which copy is to be into	*/
	*copyPtrPtr = (G_Code_Msg_t*)malloc(sizeof(G_Code_Msg_t));

	/*	copy	*/
	(*copyPtrPtr)->codeClass = originalPtr->codeClass;
	(*copyPtrPtr)->code = originalPtr->code;
	(*copyPtrPtr)->paramCount = originalPtr->paramCount;
	for(u8 i=0; i<6; i++)
	{
		(*copyPtrPtr)->paramChArr[i] = originalPtr->paramChArr[i];
		(*copyPtrPtr)->paramNumArr[i] = originalPtr->paramNumArr[i];
	}
}

void G_Code_voidFreeMsg(G_Code_Msg_t* msgPtr)
{
	free(msgPtr);
}

/*
 * returns the index of the next space - if there's one -, otherwise returns
 * the size of the line string
 */
u8 G_Code_u8FindNumberEnding(char* line, u8 start)
{
	while(line[start] != ' '		&&		line[start] != '\0')
		start++;
		
	return start - 1;
}

void G_Code_voidCopyPoint(G_Code_Msg_t* msgPtr)
{
	u8 count = msgPtr->paramCount;
	u8 isCpied[3] = {0, 0, 0};

	while(count--)
	{
		u8 pointIndex = msgPtr->paramChArr[count] - 'X';
		CNC.point[pointIndex] =
			msgPtr->paramNumArr[count] *
			(f32)CNC.config.stepsPerLengthUnit[pointIndex];
		isCpied[pointIndex] = 1;
	}

	for (u8 i = 0; i < 3; i++)
	{
		if (isCpied[i] == 0)
			CNC.point[i] = CNC.prevReceivedCoordinates[i];
		else
			CNC.prevReceivedCoordinates[i] = CNC.point[i];
	}
}

void G_Code_voidCopyPointAL(G_Code_Msg_t* msgPtr)
{
	CNC.point[5] = msgPtr->paramNumArr[5];
	CNC.point[4] = msgPtr->paramNumArr[4];
	
	u8 i = 4;
	while(i--)
		CNC.point[i] =
			msgPtr->paramNumArr[i] *
			(f32)CNC.config.stepsPerLengthUnit[i/2];
}

void G_CODE_voidCopyAcceleration(G_Code_Msg_t* msgPtr)
{
	u8 count = msgPtr->paramCount;
	while(count--)
	{
		/*	TODO: steps per unit  length is not the right way to do it	*/
		if (msgPtr->paramChArr[count] == 'P')	// feed
		{
			CNC.trajectory.feedAccel =
				msgPtr->paramNumArr[count] *
				(f32)CNC.config.stepsPerLengthUnit[0] / 3600.0f;
		}
		else // if (paramCh[paramCount] == 'T')	// rapid
		{
			CNC.config.rapidAccel =
				msgPtr->paramNumArr[count] *
				(f32)CNC.config.stepsPerLengthUnit[0] / 3600.0f;
		}
	}
}

void G_Code_voidUpdateFeedRateMax(G_Code_Msg_t* msgPtr)
{
	u8 count = msgPtr->paramCount;
	while(count--)
	{
		if (msgPtr->paramChArr[count] == 'F')
		{
			CNC.trajectory.feedrateMax =
				msgPtr->paramNumArr[count] *
				(f32)CNC.config.stepsPerLengthUnit[0] / 60.0f;
		}
	}
}

b8 G_Code_b8ParseLine(G_Code_Msg_t* msgPtr, char* line)
{
	/*	make the whole line upper case	*/
	strupr(line);

	u8 endIndex;
	/*	get code class	*/
	msgPtr->codeClass = line[0];
	/*	check it	*/
	if (msgPtr->codeClass != 'M'	&&		msgPtr->codeClass != 'G')
		return false;
	
	/*	get code number	*/
	endIndex = G_Code_u8FindNumberEnding(line, 2);
	/*	check it	*/
	if (!Math_b8IsNumber(line, 1, endIndex))
		return false;

	msgPtr->code = Math_f32StrToFloat(line, 1, endIndex);
	
	/*	get parameters	*/
	msgPtr->paramCount = 0;
	while(line[++endIndex] != '\0')
	{
		msgPtr->paramChArr[msgPtr->paramCount] = line[++endIndex];
		u8 tempEndIndex = endIndex + 1;
		endIndex = G_Code_u8FindNumberEnding(line, tempEndIndex);
		if (!Math_b8IsNumber(line, tempEndIndex, endIndex))
			return false;
		msgPtr->paramNumArr[msgPtr->paramCount++] =
			Math_f32StrToFloat(line, tempEndIndex, endIndex);
	}

	/*	if all typo checks pass	*/
	return true;
}
