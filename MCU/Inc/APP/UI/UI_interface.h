/*
 * UI_interface.h
 *
 *  Created on: Jul 14, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_APP_UI_UI_INTERFACE_H_
#define INCLUDE_APP_UI_UI_INTERFACE_H_

typedef struct{
	Rotary_Encoder_t rotary;
	Button_t button;
	TFT2_t tft;
	u8 lineCounter;
}UI_t;

/*	parameters must be initialized first	*/
void UI_voidInit(UI_t* ui);

void UI_voidClear(UI_t* ui);

void UI_voidPrintStr(UI_t* ui, char* str);

/*
 * Given a question and array of choices, lets user choose, and returns choice number.
 */
u8 UI_u8Interact(UI_t* ui, char* qStr, char* choiceStrArr[], u8 numberOfChoices);

/*
 * Sets axis speed ("CNC->manualSpeed[]") using rotary encoder, exits on press.
 */
void UI_voidSetSpeed(UI_t* ui, u32* speedArr, u8 axis);

/*
 * moves certain axis using rotary encoder with the speed in "CNC->manualSpeed[]",
 * exits if button is pressed.
 */
void UI_voidMoveAxis(UI_t* ui, Stepper_t* stepperArr, u32* speedArr, u8 axis);


#endif /* INCLUDE_APP_UI_UI_INTERFACE_H_ */
