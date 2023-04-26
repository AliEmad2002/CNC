/*
 * SDC_program.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Ali Emad
 */

/*	LIB	*/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Delay_interface.h"

/*	MCAL	*/
#include "SPI_interface.h"
#include "GPIO_interface.h"

/*	SELF	*/
#include "SDC_interface.h"
#include "SDC_CRC.h"

/*
 * Check this:
 * http://www.rjhcoding.com/avrc-sd-interface-2.php
 * http://my-cool-projects.blogspot.com/2013/06/sd-card-crc-algorithm-explained-in.html
 */
static u8 get_crc(u8* arr, u32 len)
{
	/**
	 * Study notes about CRC calculation:
	 * 		-	Simply CRC is performing a modulo operation between two
	 * 			polynomials, data polynomial and generator polynomial.
	 *
	 * 		-	Polynomials are represented like the following examples:
	 * 				0b1101   == x^3 + x^2 + 1
	 * 				0b101001 == x^5 + x^3 + 1
	 *
	 * 		-	Binary polynomial division is very similar to binary numerical
	 * 			division, except that it uses successive XOR'ing instead of
	 * 			successive subtraction.
	 *
	 * 		-	let  :	D0 = D[0:7], D1 = D[8:15], D = D[0:15]
	 *		 			C1 = CRC(D1)
	 *
	 * 			then : CRC(D) = CRC((C1 << 1) ^ D0)
	 *
	 * 			TODO: ask eng: mohamed ali, why?
	 **/
	u8 c = crcTable[0];

	for (s32 i = (s32)len - 1; i >= 0; i--)
	{
		c = crcTable[(c << 1) ^ arr[i]];
	}

	return c;
}

static send_command(u8 index, u32 arg)
{
	/**
	 * SD card uses CRC7, polynomial is 0x89
	 *
	 **/
}

void SDC_voidInitConnection(
	SDC_t* sdc, SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap)
{
	/**	Init SPI unit	**/
	sdc->spiUnitNumber = spiUnitNumber;
	SPI_voidInit(
		spiUnitNumber, SPI_Directional_Mode_Uni, SPI_DataFrameFormat_8bit,
		SPI_FrameDirection_MSB_First, SPI_Prescaler_256, SPI_Mode_Master,
		SPI_ClockPolarity_0Idle, SPI_ClockPhase_CaptureFirst);

	SPI_voidInitPins(spiUnitNumber, afioMap, 0, 1, 1);

	SPI_ENABLE_PERIPHERAL(spiUnitNumber);

	/**	Init CS pin	**/
	sdc->csPin  = csPin % 16;
	sdc->csPort = csPin / 16;
	GPIO_voidSetPinGpoPushPull(sdc->csPort, sdc->csPin);

	/**	Initialization flow: http://elm-chan.org/docs/mmc/m/sdinit.png	**/
	Delay_voidBlockingDelayMs(2);

	GPIO_SET_PIN_HIGH(sdc->csPort, sdc->csPin);

	/*	>= 74 dummy clocks	*/
	for (u8 i = 0; i < 10; i++)
		SPI_voidTransmitData(spiUnitNumber, 0xFF);

	/*	select chip	*/
	GPIO_SET_PIN_LOW(sdc->csPort, sdc->csPin);

	send_command(SDC_CMD_GO_IDLE, 0);
}










