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
#include "STK_interface.h"
#include "SPI_interface.h"
#include "GPIO_interface.h"

/*	SELF	*/
#include "SDC_Private.h"
#include "SDC_interface.h"
#include "SDC_CRC.h"


/*******************************************************************************
 * CRC calculation:
 ******************************************************************************/
/*
 * Check this:
 * http://www.rjhcoding.com/avrc-sd-interface-2.php
 * http://my-cool-projects.blogspot.com/2013/06/sd-card-crc-algorithm-explained-in.html
 * https://bits4device.wordpress.com/2017/12/16/sd-crc7-crc16-implementation/
 */
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
static u8 get_crc7(u8* arr, u32 len)
{
	u8 c = crc7Table[0];

	for (s32 i = (s32)len - 1; i >= 0; i--)
	{
		/*	TODO: Ask why	*/
		c = crc7Table[(c << 1) ^ arr[i]];
	}

	return c;
}

static u16 get_crc16(u8* arr, u32 len)
{
	u16 c = crc16Table[0];

	for (u32 i = 0; i < len; i++)
	{
		/*	TODO: Ask why	*/
		c = (c<<8) ^ crc16Table[(u8)(c>>8) ^ arr[i]];
	}

	return c;
}

/*******************************************************************************
 * Command sending and responses:
 ******************************************************************************/
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

	// send it over SPI:
	SPI_voidTransmitArrMsFirst(sdc->spiUnitNumber, cmdFrame, 6);
}

static u8 get_rData(SDC_t* sdc, SDC_Data_Response_t* response)
{
	/*	get R	*/
	u8* u8Response = (u8*)response;
	*u8Response = SPI_u8TransceiveData(sdc->spiUnitNumber, 0xFF);

	/*	check start and end bits	*/
	if (response->startBit != 1 || response->endBit != 0)
		return 0;

	/*
	 * wait for busy flag to be cleared (MISO pin is driven low as long as the busy
	 * flag is set.
	 */
	while(SPI_u8TransceiveData(sdc->spiUnitNumber, 0xFF) == 0);

	return 1;
}

/*
 * Receives response with a time out of 8 SPI bytes. as:
 * "The response is sent back within command response time (NCR), 0 to 8 bytes
 * for SDC, 1 to 8 bytes for MMC".
 *
 * Returns 1 if received, 0 otherwise.
 */
static u8 get_r1(SDC_t* sdc, SDC_R1_t* response)
{
	volatile u8 data;
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

static u8 get_r3(SDC_t* sdc, SDC_R3_t* response)
{
	// get R1 of this R3 response:
	u8 gotR1 = get_r1(sdc, &(response->r1));
	if (!gotR1)
		return 0;
	if (
		response->r1.addressErr	  	||
		response->r1.cmdCrcErr  	||
		response->r1.eraseSeqErr   	||
		response->r1.illigalCmdErr 	||
		response->r1.parameterErr
	)
		return 0;

	// get rest of R3 response (OCR value):
	SPI_voidReceiveArrMsFirst(sdc->spiUnitNumber, (u8*)response, 4);

	return 1;
}

static u8 get_r7(SDC_t* sdc, SDC_R7_t* response)
{
	// get R1 of this R7 response:
	u8 gotR1 = get_r1(sdc, &(response->r1));
	if (!gotR1)
		return 0;
	if (
		response->r1.addressErr	  	||
		response->r1.cmdCrcErr  	||
		response->r1.eraseSeqErr   	||
		response->r1.illigalCmdErr 	||
		response->r1.parameterErr
	)
		return 0;

	// get rest of R7 response:
	SPI_voidReceiveArrMsFirst(sdc->spiUnitNumber, (u8*)response, 4);

	return 1;
}

static void send_acmd(SDC_t* sdc, u8 index, u32 arg)
{
	/*	send leading CMD55	*/
	send_command(sdc, 55, 0);

	/*	Receive R1	*/
	SDC_R1_t r1;
	u8 gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
	{
		trace_printf("SD-card cmd55 failed. No response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr  	||
		r1.inIdleState != 1
	)
	{
		trace_printf("SD-card cmd55 failed. error response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}

	/*	Now send command	*/
	send_command(sdc, index, arg);
}

static SDC_OCR_t get_ocr(SDC_t* sdc)
{
	SDC_R3_t r3;
	u8 gotR3;

	/*	send CMD58	*/
	send_command(sdc, 58, 0);

	/*	get response (R3)	*/
	gotR3 = get_r3(sdc, &r3);
	if (!gotR3)
	{
		trace_printf("SD-card failed. Can't get OCR value");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}

	return r3.ocr;
}

static void set_block_len(SDC_t* sdc, u32 len)
{
	SDC_R1_t r1;
	u8 gotR1;

	send_command(sdc, 16, len);

	/*	get response (R1)	*/
	gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
	{
		trace_printf("SD-card failed. No response on setting block size");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr
	)
	{
		trace_printf("SD-card failed. error response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}
}

static void write_crc_enable(SDC_t* sdc, u8 crcEnable)
{
	SDC_R1_t r1;
	u8 gotR1;

	/*	Send CMD59 (Enable / Disable CRC)	*/
	sdc->crcEnabled = crcEnable;
	send_command(sdc, 59, crcEnable);

	/*	get response (R1)	*/
	gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
	{
		trace_printf("SD-card failed. No response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr
	)
	{
		trace_printf("SD-card failed. error response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}
}

/*
 * Following are the branches labeled on the initialization flow diagram, each
 * branch has a timeout of 1 second.
 * (Diagram is at the directory: ../Inc/HAL/SDC)
 */
#define INIT_LOOP_TIMEOUT_MS		10000
ALWAYS_INLINE_STATIC SDC_Version_t init_branch_2(SDC_t* sdc)
{
	SDC_R1_t r1;
	u8 gotR1;

	u64 startTime = STK_u64GetElapsedTicks();

	while(STK_u64GetElapsedTicks() - startTime < STK_TICKS_PER_MS * INIT_LOOP_TIMEOUT_MS)
	{
		/*	send CMD1	*/
		send_command(sdc, 1, 0);

		/*	get response (R1)	*/
		gotR1 = get_r1(sdc, &r1);
		if (!gotR1)	// if no response:
			return SDC_Version_Unknown;

		else if (	// if error response:
			r1.addressErr	  	||
			r1.cmdCrcErr  		||
			r1.eraseSeqErr   	||
			r1.illigalCmdErr 	||
			r1.parameterErr
		)
			return SDC_Version_Unknown;

		if (r1.inIdleState == 1) // card needs more time:
			continue;

		else	// card has received and processed the ACMD41 successfully
			return SDC_Version_3;
	}

	// if timeout period passed:
	return SDC_Version_Unknown;
}

ALWAYS_INLINE_STATIC SDC_Version_t init_branch_1(SDC_t* sdc)
{
	SDC_R1_t r1;
	u8 gotR1;

	u64 startTime = STK_u64GetElapsedTicks();

	while(STK_u64GetElapsedTicks() - startTime < STK_TICKS_PER_MS * INIT_LOOP_TIMEOUT_MS)
	{
		/*	send ACMD41	*/
		send_acmd(sdc, 41, 0);

		/*	get response (R1)	*/
		gotR1 = get_r1(sdc, &r1);
		if (!gotR1)	// if no response:
			return init_branch_2(sdc);

		else if (	// if error response:
			r1.addressErr	  	||
			r1.cmdCrcErr  		||
			r1.eraseSeqErr   	||
			r1.illigalCmdErr 	||
			r1.parameterErr
		)
			return init_branch_2(sdc);

		if (r1.inIdleState == 1) // card needs more time:
			continue;

		else	// card has received and processed the ACMD41 successfully
			return SDC_Version_1;
	}

	// if timeout period passed:
	return init_branch_2(sdc);
}

ALWAYS_INLINE_STATIC SDC_Version_t init_branch_0(SDC_t* sdc)
{
	SDC_R1_t r1;
	u8 gotR1;

	u64 startTime = STK_u64GetElapsedTicks();

	while(STK_u64GetElapsedTicks() - startTime < STK_TICKS_PER_MS * INIT_LOOP_TIMEOUT_MS)
	{
		/*	send ACMD41	*/
		send_acmd(sdc, 41, 1 << 30);

		/*	get response (R1)	*/
		gotR1 = get_r1(sdc, &r1);
		if (!gotR1)	// if no response:
		{
			trace_printf("exit1\n");
			return SDC_Version_Unknown;
		}

		else if (	// if error response:
			r1.addressErr	  	||
			r1.cmdCrcErr  		||
			r1.eraseSeqErr   	||
			r1.illigalCmdErr 	||
			r1.parameterErr
		)
		{
			trace_printf("exit2\n");
			return SDC_Version_Unknown;
		}

		if (r1.inIdleState == 1) // card needs more time:
		{
			Delay_voidBlockingDelayMs(100);
			continue;
		}

		else	// card has received and processed the ACMD41 successfully
		{
			/*	read card's OCR	*/
			SDC_OCR_t ocr = get_ocr(sdc);

			if (ocr.ccs == 0)
				return SDC_Version_2_ByteAddress;
			else
				return SDC_Version_2_BlockAddress;
		}
	}

	// if timeout period passed:
	trace_printf("exit3\n");
	return SDC_Version_Unknown;
}

void SDC_voidInitConnection(
	SDC_t* sdc, u8 crcEnable,
	SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap)
{
	SDC_R1_t r1;
	SDC_R7_t r7;
	u8 gotR1;
	u8 gotR7;

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

	/**	Initialization flow: (Diagram is at the directory: ../Inc/HAL/SDC)	**/
	Delay_voidBlockingDelayMs(2);

	GPIO_SET_PIN_HIGH(sdc->csPort, sdc->csPin);

	/*	>= 74 dummy clocks	*/
	for (u8 i = 0; i < 10; i++)
		SPI_voidTransmitData(spiUnitNumber, 0xFF);

	/*	select chip	*/
	GPIO_SET_PIN_LOW(sdc->csPort, sdc->csPin);

	/*	send CMD0	*/
	send_command(sdc, 0, 0);

	/*	get response (R1)	*/
	gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
	{
		trace_printf("SD-card initialization failed. No response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr  	||
		r1.inIdleState != 1
	)
	{
		trace_printf("SD-card initialization failed. error response");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}

	/*	send CMD8	*/
	send_command(sdc, 8, 0x000001AA);

	/*	get response (R7)	*/
	gotR7 = get_r7(sdc, &r7);

	if (!gotR7)	// if no response:
		sdc->ver = init_branch_1(sdc);

	else if (r7.checkPattern == 0xAA && r7.voltageAccepted == 1)
		sdc->ver = init_branch_0(sdc);

	else	// mismatch
		sdc->ver = SDC_Version_Unknown;

	/*	if version is unknown	*/
	if (sdc->ver == SDC_Version_Unknown)
	{
		trace_printf("SD-card initialization failed. Unknown version");
		u8 stop = 1;
		__asm volatile ("bkpt 0");
		while(stop);
	}

	/*	if version is known and other than "SDC_Version_2_BlockAddress"	*/
	if (sdc->ver != SDC_Version_2_BlockAddress)
	{
		/*	set block len to 512 bytes (CMD16)	*/
		set_block_len(sdc, 512);
	}

	/*	Enable / Disable CRC	*/
	write_crc_enable(sdc, crcEnable);
}

/*	prints block (debug only)	*/
static void print_block(u8* block)
{
	trace_printf("0x");
	for (s16 i = 511; i >= 0; i--)
	{
		trace_printf("%X", (s32)block[i]);
	}
}

u8 SDC_u8WriteBlock(SDC_t* sdc, u8* block, u32 blockNumber)
{
	SDC_R1_t r1;
	SDC_Data_Response_t rd;

	u8 gotR1;
	u8 gotRd;

	/*	Send CMD24	*/
	send_command(sdc, 24, blockNumber);

	/*	Get R1 response	*/
	gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
		return 0;
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr
	)
		return 0;

	/*	if CRC was enabled, calculate it for the block	*/
	u16 crc = 0;
	if (sdc->crcEnabled == 1)
		crc = get_crc16(block, 512);

	/*	wait for 1 SPI byte	*/
	SPI_voidTransmitData(sdc->spiUnitNumber, 0xFF);

	/**	send the data packet	**/
	/*	send data token	*/
	SPI_voidTransmitData(sdc->spiUnitNumber, 0b11111110);
	/*	send data block	*/
	SPI_voidTransmitArrMsFirst(sdc->spiUnitNumber, block, 512);
	/*	send CRC	*/
	SPI_voidTransmitArrMsFirst(sdc->spiUnitNumber, (u8*)&crc, 2);

	/*	Get data response	*/
	gotRd = get_rData(sdc, &rd);
	if (!gotRd)
		return 0;
	if (
		!rd.accepted		||
		rd.crcErr	  		||
		rd.wrtErr
	)
		return 0;

	return 1;
}

u8 SDC_u8ReadBlock(SDC_t* sdc, u8* block, u32 blockNumber)
{
	SDC_R1_t r1;
	u8 gotR1;

	/*	Send CMD17	*/
	send_command(sdc, 17, blockNumber);

	/*	Get R1 response	*/
	gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
		return 0;
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr
	)
		return 0;

	/*	wait for the data token (0b11111110) to be received, with a timeout of 1 second	*/
	u64 startTime = STK_u64GetElapsedTicks();
	while(1)
	{
		if (SPI_u8TransceiveData(sdc->spiUnitNumber, 0xFF) == 0b11111110)
			break;

		if (STK_u64GetElapsedTicks() - startTime >= 1000 * STK_TICKS_PER_MS)
			return 0;
	}

	/*	Receive the data block	*/
	SPI_voidReceiveArrLsFirst(sdc->spiUnitNumber, block, 512);

	/*	Receive the CRC	*/
	u16 crc;
	SPI_voidReceiveArrMsFirst(sdc->spiUnitNumber, (u8*)&crc, 2);

	//print_block(block);

	/*	Check CRC (if enabled)	*/
	if (sdc->crcEnabled)
	{
		u16 crcCalc = get_crc16(block, 512);
		if (crcCalc != crc)
			return 0;
	}

	return 1;
}






