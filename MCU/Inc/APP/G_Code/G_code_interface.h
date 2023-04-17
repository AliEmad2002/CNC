/*
 * G_code_interface.h
 *
 * Created: 7/13/2022 9:54:24 PM
 *  Author: Ali Emad
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
	G_CODE_setSpindleSpeedCW =		3,
	G_CODE_setSpindleSpeedCCW =		4,
	G_CODE_turnSpindleOff = 		5,
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

void G_Code_voidFreeMsg(G_Code_Msg_t* msgPtr);

u8 G_Code_u8FindNumberEnding(char* line, u8 start);

void G_Code_voidCopyPoint(s32* point, G_Code_Msg_t* msgPtr);

void G_Code_voidCopyPointAL(s32* point, G_Code_Msg_t* msgPtr);

void G_CODE_voidCopyAcceleration(u32 mainParametersArr[], G_Code_Msg_t* msgPtr);

b8 G_Code_b8ParseLine(G_Code_Msg_t* msgPtr, char* line);



#endif /* G-CODE_INTERFACE_H_ */
