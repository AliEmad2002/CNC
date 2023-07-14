/*
 * UI_program.c
 *
 *  Created on: Jul 14, 2023
 *      Author: ali20
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Txt_interface.h"

/*	MCAL	*/
#include "RCC_interface.h"
#include "DMA_interface.h"
#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "TIM_interface.h"

/*	HAL	*/
#include "TFT_interface_V2.h"
#include "Rotary_Encoder_Interface.h"
#include "Button_interface.h"
#include "Stepper_interface.h"

/*	SELF	*/
#include "UI_interface.h"


void UI_voidInit(UI_t* ui)
{
	Rotary_Encoder_voidInit(&(ui->rotary));
	Button_voidInit(&(ui->button));
	ui->lineCounter = 0;
}

void UI_voidClear(UI_t* ui)
{
	TFT2_voidClearDisplay(&(ui->tft));
	ui->lineCounter = 0;
}

void UI_voidPrintStr(UI_t* ui, char* str)
{
	u8 charCount = 0;
	char ch;
	u16 pixArr[8 * 6];
	u8 xStart = 128 - 8 - 8 * ui->lineCounter;
	u8 yStart = 0;

	TFT2_SET_X_BOUNDARIES(&(ui->tft), xStart, xStart+7)

	while(1)
	{
		ch = str[charCount];

		if (ch == '\0' || charCount == 32)
		{
			TFT2_voidWaitCurrentDataTransfer(&(ui->tft));
			TFT2_SET_Y_BOUNDARIES(&(ui->tft), yStart, 159);
			u16 color = 0;
			TFT2_voidFillDMA(&(ui->tft), &color, 8 * (160-yStart));
			return;
		}

		Txt_voidPrintCharOnPixArrRigthOrientation(ch, 65535, 0, 0, 0, pixArr, 6);
		TFT2_voidWaitCurrentDataTransfer(&(ui->tft));
		TFT2_SET_Y_BOUNDARIES(&(ui->tft), yStart, yStart+5);
		TFT2_voidSendPixels(&(ui->tft), pixArr, 8 * 6);

		charCount++;
		yStart += 6;
	}

	ui->lineCounter++;
}

u8 UI_u8Interact(UI_t* ui, char* qStr, char* choiceStrArr[], u8 numberOfChoices)
{
	UI_voidPrintStr(ui, qStr);

	u8 startLineCount = ui->lineCounter;

	u8 currentCount = 0;

	ui->button.isPressed = 0;

	ui->rotary.count = 0;

	char str[128];

	while(1)
	{
		/*	print choices list, with "currentCount" choice appended to an arrow	*/
		ui->lineCounter = startLineCount;
		for (u8 i = 0; i < numberOfChoices; i++)
		{
			if (i == currentCount)
			{
				sprintf(str, "->%s", choiceStrArr[i]);
				UI_voidPrintStr(ui, str);
			}

			else
				UI_voidPrintStr(ui, choiceStrArr[i]);
		}

		/*	wait for rotary to be rotated or button to be pressed	*/
		while(1)
		{
			if (ui->button.isPressed)
			{
				ui->button.isPressed = 0;
				return currentCount;
			}

			else if (ui->rotary.count != 0)
			{
				if (ui->rotary.count < 0)
				{
					if (currentCount == 0)
						currentCount = numberOfChoices - 1;
					else
						currentCount--;
				}

				else
				{
					if (currentCount == numberOfChoices - 1)
						currentCount = 0;
					else
						currentCount++;
				}

				ui->rotary.count = 0;

				break;
			}
		}
	}
}

void UI_voidSetSpeed(UI_t* ui, u32* speedArr, u8 axis)
{
	char str[32];
	char axisChArr[] = {'x', 'y', 'z'};

	sprintf(str, "Set %c axis speed", axisChArr[axis]);
	UI_voidPrintStr(ui, str);
	UI_voidPrintStr(ui, "Use rotary to change speed,");
	UI_voidPrintStr(ui, "Press button to exit.");
	u8 startLineCount = ui->lineCounter;

	ui->rotary.count = 0;

	while(1)
	{
		/*	print current value of speed	*/
		ui->lineCounter = startLineCount;
		sprintf("speed = %d mm/rev", (s32)speedArr[axis]);

		/*	wait for rotary to be rotated or button to be pressed	*/
		while(1)
		{
			if (ui->button.isPressed)
			{
				ui->button.isPressed = 0;
				return;
			}

			else if (ui->rotary.count != 0)
			{
				s32 speed = (s32)speedArr[axis] + ui->rotary.count;

				if (speed < 0)
					speedArr[axis] = 0;
				else
					speedArr[axis] = speed;

				ui->rotary.count = 0;

				break;
			}
		}
	}
}

void UI_voidMoveAxis(UI_t* ui, Stepper_t* stepperArr, u32* speedArr, u8 axis)
{
	char str[32];
	char axisChArr[] = {'x', 'y', 'z'};

	sprintf(str, "Move %c axis", axisChArr[axis]);
	UI_voidPrintStr(ui, str);
	UI_voidPrintStr(ui, "Use rotary to move,");
	UI_voidPrintStr(ui, "Press button to exit.");
	u8 startLineCount = ui->lineCounter;

	ui->rotary.count = 0;

	u32 steps;
	Stepper_Direction_t dir;
	u64 currentTime;

	while(1)
	{
		/*	wait for rotary to be rotated or button to be pressed	*/
		while(1)
		{
			if (ui->button.isPressed)
			{
				ui->button.isPressed = 0;
				return;
			}

			else if (ui->rotary.count != 0)
			{
				if (ui->rotary.count < 0)
				{
					dir = Stepper_Direction_backward;
					steps = (-ui->rotary.count) * 800 * speedArr[axis];
				}
				else
				{
					dir = Stepper_Direction_forward;
					steps = ui->rotary.count * 800 * speedArr[axis];
				}

				while(steps--)
				{
					currentTime = STK_u64GetElapsedTicks() ;
					while(currentTime - stepperArr[axis].lastTimeStamp < 4000);
					Stepper_voidStep(&stepperArr[axis], dir, currentTime);
				}

				ui->rotary.count = 0;

				break;
			}
		}
	}
}
