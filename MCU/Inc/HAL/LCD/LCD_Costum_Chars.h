/*
 * LCD_Costum_Chars.h
 *
 *  Created on:	Aug 23, 2022
 *  Author:		Ali Emad Ali
 *	
 *	Resources:
 *		*
 *
 */

#ifndef LCD_COSTUM_CHARS_H_
#define LCD_COSTUM_CHARS_H_

u8 lockedLockPattern[] = {0b01110, 0b10001, 0b10001, 0b11111, 0b11011, 0b11011, 0b11011, 0b00000};

u8 unlockedLockPattern[] = {0b01110, 0b10000, 0b10000, 0b11111, 0b11011, 0b11011, 0b11011, 0b00000};

// accessed by 'char' - '!' (as it is the least of the alphabet used in this driver).
u8 invertedAlphabet[][8] ={
		/*	'i'	*/
		{0b11011, 0b11011, 0b11011, 0b11011, 0b11111, 0b11111, 0b11011, 0b11111},

		/*	'"'	*/
		{0b10101, 0b10101, 0b10101, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},

		/*	'#'	*/
		{0b10101, 0b10101, 0b00000, 0b10101, 0b00000, 0b10101, 0b10101, 0b11111},

		/*	'$'	*/
		{0b11011, 0b10000, 0b01011, 0b10001, 0b11010, 0b00001, 0b11011, 0b11111},

		/*	'%'	*/
		{0b00111, 0b00110, 0b11101, 0b11011, 0b10111, 0b01100, 0b11100, 0b11111},

		/*	'&'	*/
		{0b10011, 0b01101, 0b01011, 0b10111, 0b01010, 0b01101, 0b10010, 0b11111},

		/*	'\''	*/
		{0b10011, 0b11011, 0b10111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},

		/*	'('	*/
		{0b11101, 0b11011, 0b10111, 0b10111, 0b10111, 0b11011, 0b11101, 0b11111},

		/*	')'	*/
		{0b10111, 0b11011, 0b11101, 0b11101, 0b11101, 0b11011, 0b10111, 0b11111},

		/*	'*'	*/
		{0b11111, 0b11011, 0b01010, 0b10001, 0b01010, 0b11011, 0b11111, 0b11111},

		/*	'+'	*/
		{0b11111, 0b11011, 0b11011, 0b00000, 0b11011, 0b11011, 0b11111, 0b11111},

		/*	','	*/
		{0b11111, 0b11111, 0b11111, 0b11111, 0b10011, 0b11011, 0b10111, 0b11111},

		/*	'-'	*/
		{0b11111, 0b11111, 0b11111, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111},

		/*	'.'	*/
		{0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b10011, 0b10011, 0b11111},

		/*	'/'	*/
		{0b11111, 0b11110, 0b11101, 0b11011, 0b10111, 0b01111, 0b11111, 0b11111},

		/*	'0'	*/
		{0b10001, 0b01110, 0b01100, 0b01010, 0b00110, 0b01110, 0b10001, 0b11111},
};

#endif /* LCD_COSTUM_CHARS_H_ */
