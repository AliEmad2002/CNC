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

/*
 * Check this:
 * http://www.rjhcoding.com/avrc-sd-interface-2.php
 * http://my-cool-projects.blogspot.com/2013/06/sd-card-crc-algorithm-explained-in.html
 */

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










