/*
 * G_code_program.c
 *
 * Created: 7/13/2022 9:54:36 PM
 *  Author: Ali Emad
 */ 

/*	LIB	*/
#include "STD_TYPES.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*	MCAL	*/
#include "UART_interface.h"

/*	APP CONFIG (some params are config dependent)	*/
#include "CNC_config.h"

/*	self	*/
#include "G_code_interface.h"

#define ACCELFEED_INDEX		1
#define ACCELRAPID_INDEX	2

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

void G_Code_voidFreeMsg(G_Code_Msg_t** msgPtrPtr)
{
	free(*msgPtrPtr);
}

s16 str_find(char* str, char ch, s16 start)
{
	for (s16 i=start; str[i]!='\0'; i++)
		if (str[i] == ch)
			return i;
			
	return -1;
}

f32 str_to_float(char* str, s16 start, s16 end)
{
	f32 n = 0.0f;

	u8 negative = 0;
	if (str[start] == '-')
	{
		negative = 1;
		start++;
	}

	u8 point = 0;
	s16 pointIndex;
	for (pointIndex = start; pointIndex <= end; pointIndex++)
	{
		if (str[pointIndex] == '.')
		{
			point = 1;
			break;
		}
		else if (str[pointIndex] == 'e')
			break;
	}
	
	u8 e = 0;
	s16 eIndex;
	for (eIndex = end - 1; eIndex > start; eIndex--)
		if (str[eIndex] == 'e')
		{
			e = 1;
			break;
		}
	if (!e)
		eIndex = end + 1;
	
	f32 decadeCounter = 1.0;
	for (s16 i = pointIndex - 1; i >= start; i--)
	{
		n += decadeCounter * (f32)(str[i] - '0');
		decadeCounter *= 10.0;
	}

	if (point)
	{
		f32 fDecadeCounter = 0.1;
		for (s16 i = pointIndex + 1; i <= eIndex - 1; i++)
		{
			n += fDecadeCounter * (f32)(str[i] - '0');
			fDecadeCounter /= 10.0;
		}
	}
	
	if (e)
	{
		f32 power = str_to_float(str, eIndex + 1, end);
		n *= (f32)pow(10.0, power);
	}
	
	return n * (negative ? -1.0 : 1.0);
}

/*	returns the index of the next space - if there's one -, otherwise returns the size of the line string	*/
u8 find_number_ending(char* line, u8 start)
{
	while(line[start] != ' '		&&		line[start] != '\0')
		start++;
		
	return start - 1;
}

void G_Code_voidCopyPoint(s32* point, G_Code_Msg_t* msgPtr)
{
	u8 count = msgPtr->paramCount;
	while(count--)
	{
		u8 pointIndex = msgPtr->paramChArr[count] - 'X';
		point[pointIndex] = msgPtr->paramNumArr[count] * (f32)STEPS_PER_MM;
	}
}

void G_Code_voidCopyPointAL(s32* point, G_Code_Msg_t* msgPtr)
{
	point[5] = msgPtr->paramNumArr[5];
	point[4] = msgPtr->paramNumArr[4];
	
	u8 i = 4;
	while(i--)
		point[i] = msgPtr->paramNumArr[i] * (f32)STEPS_PER_MM;
}

void G_CODE_voidCopyAcceleration(u32** mainParametersPtrArr, G_Code_Msg_t* msgPtr)
{
	u8 count = msgPtr->paramCount;
	while(count--)
	{
		if (msgPtr->paramChArr[count] == 'P')	// feed
		{
			*mainParametersPtrArr[ACCELFEED_INDEX] = msgPtr->paramNumArr[count] * STEPS_PER_MM;
		}
		else // if (paramCh[paramCount] == 'T')	// rapid
		{
			*mainParametersPtrArr[ACCELRAPID_INDEX] = msgPtr->paramNumArr[count] * STEPS_PER_MM;
		}
	}
}

void G_Code_voidParseLine(G_Code_Msg_t* msgPtr, char* line)
{
	u8 endIndex;
	/*	get code class	*/
	msgPtr->codeClass = line[0];
	
	/*	get code number	*/
	endIndex = find_number_ending(line, 2);
	msgPtr->code = str_to_float(line, 1, endIndex);
	
	/*	get parameters	*/
	msgPtr->paramCount = 0;
	while(line[++endIndex] != '\0')
	{
		msgPtr->paramChArr[msgPtr->paramCount] = line[++endIndex];
		u8 tempEndIndex = endIndex + 1;
		endIndex = find_number_ending(line, tempEndIndex);
		msgPtr->paramNumArr[msgPtr->paramCount++] = str_to_float(line, tempEndIndex, endIndex);
	}
}
