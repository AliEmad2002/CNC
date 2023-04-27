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
#include "diag/trace.h"

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
 * https://bits4device.wordpress.com/2017/12/16/sd-crc7-crc16-implementation/
 */
static u8 get_crc7(u8* arr, u32 len)
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
	u8 c = crc7Table[0];

	for (s32 i = (s32)len - 1; i >= 0; i--)
	{
		c = crc7Table[(c << 1) ^ arr[i]];
	}

	return c;
}

static void send_command(SDC_t* sdc, u8 index, u32 arg)
{
	// create command frame:
	u8* argPtr = (u8*)&arg;
	u8 cmdFrame[6] = {
		0b00000001, // CRC and stop bit (initially CRC is 0 as it is not yet calculated)
		argPtr[0],
		argPtr[1],
		argPtr[2],
		argPtr[3],
		0b01000000 | index	// index and start bits.
	};

	// calculate CRC and copy it to he frame:
	u8 crc = get_crc7(&cmdFrame[1], 5);
	cmdFrame[0] |= (crc << 1);

	for (unsigned int i = 0; i < 6; i++)
	{
		trace_printf("%d\n", (u32)cmdFrame[i]);
	}

	// send it over SPI:
	SPI_voidTransmitArrMsFirst(sdc->spiUnitNumber, cmdFrame, 6);
}

/*
 * Receives response with a time out of 8 SPI bytes. as:
 * "The response is sent back within command response time (NCR), 0 to 8 bytes
 * for SDC, 1 to 8 bytes for MMC".
 *
 * Returns 1 if received, 0 otherwise.
 */
static u8 get_response(SDC_t* sdc, SDC_Response_t* response)
{
	u8 data;
	for (u8 i = 0; i < 8; i++)
	{
		data = SPI_u8TransceiveData(sdc->spiUnitNumber, 0xFF);
		if (data != 0xFF)	// response start bit is received
		{
			if (GET_BIT(data, 7) == 0) // if MSB of "data" is the start bit
				*((u8*)response) = data;

			else
			{
				trace_printf("start bit odd case has tto be implemented");
				__asm volatile ("bkpt 0");
			}

//			else // otherwise, a bit in the middle of "data" is the start bit
//			{
//				// receive the next byte:
//				u8 data2 = SPI_u8TransceiveData(sdc->spiUnitNumber, 0xFF);
//
//				// merge the two bytes:
//				u16 data16 = (u16)data << 8 | data2;
//
//				// shift "data16" right until the start bit is in place of bit #7
//
//				// copy "data16[0:7]" to "*response"
//			}
			return 1;
		}
	}

	return 0;
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

	/*	send CMD0	*/
	send_command(sdc, 0, 0);

	/*	get response	*/
	SDC_Response_t resp;
	u8 gotResp = get_response(sdc, &resp);
	if (!gotResp)
	{
		trace_printf("SD-card initialization failed. No response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}

	if (
		resp.r1.addressErr	  	||
		resp.r1.cmdCrcErr  	  	||
		resp.r1.eraseSeqErr   	||
		resp.r1.illigalCmdErr 	||
		resp.r1.parameterErr  	||
		resp.r1.inIdleState != 1
	)
	{
		trace_printf("SD-card initialization failed. error response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}



}










