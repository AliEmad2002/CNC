/*
 * G_code_interface.h
 *
 * Created: 7/13/2022 9:54:24 PM
 *
 * Copyright (c) 2022, Ali Emad
 * All rights reserved.
 *
 * This source code is licensed under the GPL-style license found in the
 * LICENSE file in the root directory of this source tree. 
 */


#ifndef G_CODE_INTERFACE_H_
#define G_CODE_INTERFACE_H_

enum G_CODE_G_COEDES {
	G_CODE_rapidMovement =			0,
	G_CODE_feedMovement =			1,
	G_CODE_autoLeveling =			29,
	G_CODE_singleProbe =			30,
	G_CODE_abslutePositioning =		90,
	G_CODE_relativePositioning =	91,
	G_CODE_softwareSetPosition =	92
	};
	
enum G_CODE_M_COEDES {
	G_CODE_setMaxFeedrate =			203,
	G_CODE_setAcceleration =		204,
	G_CODE_enableAutoLeveling =		420
};

typedef struct{
	char codeClass;
	u16 code;
	u8 paramCount;
	char paramChArr[6];
	f32 paramNumArr[6];
}G_Code_Msg_t;

void G_Code_voidCopyMsg(G_Code_Msg_t** copyPtrPtr, G_Code_Msg_t* originalPtr);

void G_Code_voidFreeMsg(G_Code_Msg_t** msgPtrPtr);

s16 str_find(char* str, char ch, s16 start);

f32 str_to_float(char* str, s16 start, s16 end);

u8 find_number_ending(char* line, u8 start);

void G_Code_voidCopyPoint(s32* point, G_Code_Msg_t* msgPtr);

void G_Code_voidCopyPointAL(s32* point, G_Code_Msg_t* msgPtr);

void G_CODE_voidCopyAcceleration(u32** mainParametersPtrArr, G_Code_Msg_t* msgPtr);

void G_Code_voidParseLine(G_Code_Msg_t* msgPtr, char* line);



#endif /* G-CODE_INTERFACE_H_ */
