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
#include <ctype.h>

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
	volatile u8 data;
	for (u8 i = 0; i < 8; i++)
	{
		data = SPI_u8TransceiveData(sdc->spiUnitNumber, 0xFF);
		if (data != 0xFF)	// response start bit is received
		{
			*((u8*)response) = data;
			break;
		}
	}

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
			*((u8*)response) = data;
			if (GET_BIT(data, 7) != 0) // if MSB of "data" is the start bit
			{
				//trace_printf("start bit odd case has tto be implemented");
				//__asm volatile ("bkpt 0");
				return 0;
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

static u8 send_acmd(SDC_t* sdc, u8 index, u32 arg)
{
	/*	send leading CMD55	*/
	send_command(sdc, 55, 0);

	/*	Receive R1	*/
	SDC_R1_t r1;
	u8 gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
		return 0;
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr  	||
		r1.inIdleState != 1
	)
		return 0;

	/*	Now send command	*/
	send_command(sdc, index, arg);

	return 1;
}

static u8 get_ocr(SDC_t* sdc, SDC_OCR_t* ocr)
{
	SDC_R3_t r3;
	u8 gotR3;

	/*	send CMD58	*/
	send_command(sdc, 58, 0);

	/*	get response (R3)	*/
	gotR3 = get_r3(sdc, &r3);
	if (!gotR3)
		return 0;

	*ocr = r3.ocr;

	return 1;
}

static u8 set_block_len(SDC_t* sdc, u32 len)
{
	SDC_R1_t r1;
	u8 gotR1;

	send_command(sdc, 16, len);

	/*	get response (R1)	*/
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

	return 1;
}

static u8 write_crc_enable(SDC_t* sdc, u8 crcEnable)
{
	SDC_R1_t r1;
	u8 gotR1;

	/*	Send CMD59 (Enable / Disable CRC)	*/
	sdc->crcEnabled = crcEnable;
	send_command(sdc, 59, crcEnable);

	/*	get response (R1)	*/
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

	return 1;
}

/*******************************************************************************
 * Init:
 ******************************************************************************/
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
	u8 successfull;

	u64 startTime = STK_u64GetElapsedTicks();

	while(STK_u64GetElapsedTicks() - startTime < STK_TICKS_PER_MS * INIT_LOOP_TIMEOUT_MS)
	{
		/*	send ACMD41	*/
		successfull = send_acmd(sdc, 41, 0);
		if (!successfull)
			return SDC_Version_Unknown;

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
	u8 successfull;

	u64 startTime = STK_u64GetElapsedTicks();

	while(STK_u64GetElapsedTicks() - startTime < STK_TICKS_PER_MS * INIT_LOOP_TIMEOUT_MS)
	{
		/*	send ACMD41	*/
		successfull = send_acmd(sdc, 41, 1 << 30);
		if (!successfull)
			return SDC_Version_Unknown;

		/*	get response (R1)	*/
		gotR1 = get_r1(sdc, &r1);
		if (!gotR1)	// if no response:
		{
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
			return SDC_Version_Unknown;
		}

		if (r1.inIdleState == 1) // card needs more time:
		{
			continue;
		}

		else	// card has received and processed the ACMD41 successfully
		{
			/*	read card's OCR	*/
			SDC_OCR_t ocr;
			successfull = get_ocr(sdc, &ocr);
			if (!successfull)
				return SDC_Version_Unknown;

			if (ocr.ccs == 0)
				return SDC_Version_2_ByteAddress;
			else
				return SDC_Version_2_BlockAddress;
		}
	}

	// if timeout period passed:
	return SDC_Version_Unknown;
}

static u8 init_flow(SDC_t* sdc)
{
	SDC_R1_t r1;
	SDC_R7_t r7;
	u8 gotR1;
	u8 gotR7;
	u8 successfull;

	SPI_voidSetBaudRatePrescaler(sdc->spiUnitNumber, SPI_Prescaler_256);

	/*	Initially, no sectors have been read yet	*/
	sdc->lbaRead = 0xFFFFFFFF;

	/**	Initialization flow: (Diagram is at the directory: ../Inc/HAL/SDC)	**/
	GPIO_SET_PIN_HIGH(sdc->csPort, sdc->csPin);

	Delay_voidBlockingDelayMs(2);

	/*	>= 74 dummy clocks	*/
	for (u8 i = 0; i < 10; i++)
		SPI_voidTransmitData(sdc->spiUnitNumber, 0xFF);

	/*	select chip	*/
	GPIO_SET_PIN_LOW(sdc->csPort, sdc->csPin);

	/*	send CMD0	*/
	send_command(sdc, 0, 0);

	/*	get response (R1)	*/
	gotR1 = get_r1(sdc, &r1);
	if (!gotR1)
		return 0;
	if (
		r1.addressErr	  	||
		r1.cmdCrcErr  		||
		r1.eraseSeqErr   	||
		r1.illigalCmdErr 	||
		r1.parameterErr  	||
		r1.inIdleState != 1
	)
		return 0;

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
		return 0;

	/*	if version is known and other than "SDC_Version_2_BlockAddress"	*/
	if (sdc->ver != SDC_Version_2_BlockAddress)
	{
		/*	set block len to 512 bytes (CMD16)	*/
		successfull = set_block_len(sdc, 512);
		if (!successfull)
			return 0;
	}

	/*	Enable / Disable CRC	*/
	successfull = write_crc_enable(sdc, sdc->crcEnabled);
	if (!successfull)
		return 0;

	SPI_voidSetBaudRatePrescaler(sdc->spiUnitNumber, SPI_Prescaler_2);

	return 1;
}

u8 SDC_u8InitConnection(
	SDC_t* sdc, u8 crcEnable,
	SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap)
{
	sdc->crcEnabled = crcEnable;

	/**	Init SPI unit	**/
	sdc->spiUnitNumber = spiUnitNumber;

	SPI_voidInit(
		sdc->spiUnitNumber, SPI_Directional_Mode_Uni, SPI_DataFrameFormat_8bit,
		SPI_FrameDirection_MSB_First, SPI_Prescaler_256, SPI_Mode_Master,
		SPI_ClockPolarity_0Idle, SPI_ClockPhase_CaptureFirst);

	SPI_voidInitPins(spiUnitNumber, afioMap, 0, 1, 1);

	SPI_ENABLE_PERIPHERAL(spiUnitNumber);

	/**	Init CS pin	**/
	sdc->csPin  = csPin % 16;
	sdc->csPort = csPin / 16;
	GPIO_voidSetPinGpoPushPull(sdc->csPort, sdc->csPin);

	/** Init flow	**/
	return init_flow(sdc);
}

void SDC_voidKeepTryingInitConnection(
	SDC_t* sdc, u8 crcEnable,
	SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap)
{
	u8 successfull = SDC_u8InitConnection(sdc, crcEnable, spiUnitNumber, csPin, afioMap);
	if (successfull)
		return;

	while(!init_flow(sdc));
}

u8 SDC_u8InitPartition(SDC_t* sdc)
{
	u8 successfull;

	/*	Read zero-th sector (MBR)	*/
	successfull = SDC_u8ReadBlock(sdc, sdc->block, 0);
	if (!successfull)
		return 0;

	/*	In the partition table, search for the partition that uses FAT32	*/
	SDC_Partition_Entry_t* partitionEntry;
	for (u8 i = 0; i < 4; i++)
	{
		partitionEntry = (SDC_Partition_Entry_t*)&(sdc->block[446 + 16 * i]);
		if (partitionEntry->typeCode == 0xB || partitionEntry->typeCode == 0xC)
			break;
	}

	/*	Read volume ID sector of the partition (first sector in partition)	*/
	u32 lbaBegin = partitionEntry->lbaBegin;
	successfull = SDC_u8ReadBlock(sdc, sdc->block, lbaBegin);
	if (!successfull)
		return 0;

	u16 bytesPerSector			= *(u16*)&(sdc->block[0x0B]);
	sdc->sectorsPerCluster		= *(u8 *)&(sdc->block[0x0D]);
	u16 numberOfReservedSectors	= *(u16*)&(sdc->block[0x0E]);
	u8 numberOfFats				= *(u8 *)&(sdc->block[0x10]);
	sdc->fat.sectorsPerFat		= *(u32*)&(sdc->block[0x24]);
	u32 rootDirFirstCluster		= *(u32*)&(sdc->block[0x2C]);
	u16 signature				= *(u16*)&(sdc->block[0x1FE]);

	/*	Check constant values (from "volume ID critical fields" table in the document)	*/
	if (bytesPerSector != 512)
		return 0;
	if (numberOfFats != 2)
		return 0;
	if (signature != 0xAA55)
		return 0;

	/*	Get LBA of the File Allocation Table of that partition	*/
	sdc->fat.lba = lbaBegin + numberOfReservedSectors;

	/*	Get LBA of the first cluster in root directory	*/
	sdc->clustersBeginLba = sdc->fat.lba + numberOfFats * sdc->fat.sectorsPerFat;

	return 1;
}

void SDC_voidKeepTryingInitPartition(SDC_t* sdc)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{
			successfull = SDC_u8InitPartition(sdc);
			if (successfull)
				return;
		}

		while(!init_flow(sdc));
	}
}

/*******************************************************************************
 * Write / Read block:
 ******************************************************************************/
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
	SPI_voidTransmitArrLsFirst(sdc->spiUnitNumber, block, 512);
	/*	send CRC	*/
	SPI_voidTransmitArrMsFirst(sdc->spiUnitNumber, (u8*)&crc, 2);

	/*	Get data response	*/
	gotRd = get_rData(sdc, &rd);
	if (!gotRd)
		return 0;
	if (rd.status != SDC_Data_Response_Status_Accepted)
		return 0;

	return 1;
}

void SDC_voidKeepTryingWriteBlock(SDC_t* sdc, u8* block, u32 blockNumber)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{
			successfull = SDC_u8WriteBlock(sdc, block, blockNumber);
			if (successfull)
				return;
		}

		while(!init_flow(sdc));
	}
}

u8 SDC_u8ReadBlock(SDC_t* sdc, u8* block, u32 blockNumber)
{
	SDC_R1_t r1;
	u8 gotR1;

	/*	if the block requested is the one currently in SD-card's object buffer	*/
	if (blockNumber == sdc->lbaRead)
		return 1;

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

	/*	Check CRC (if enabled)	*/
	if (sdc->crcEnabled)
	{
		u16 crcCalc = get_crc16(block, 512);
		if (crcCalc != crc)
			return 0;
	}

	sdc->lbaRead = blockNumber;
	return 1;
}

void SDC_voidKeepTryingReadBlock(SDC_t* sdc, u8* block, u32 blockNumber)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{
			successfull = SDC_u8ReadBlock(sdc, block, blockNumber);
			if (successfull)
				return;
		}

		while(!init_flow(sdc));
	}
}

/*******************************************************************************
 * Search:
 ******************************************************************************/
/*	Searches for an array of bytes in the whole card (debug only)	*/
static s32 find_in_block(u8* block, u32 blockLen, u8* byteArr, u32 len)
{
	for (u32 i = 0; i < blockLen; i++)
	{
		u8 mismatch = 0;
		for (u32 j = 0; j < len; j++)
		{
			if (block[i+j] != byteArr[j])
			{
				mismatch = 1;
				break;
			}
		}
		if (mismatch == 0)
			return i;
	}

	return -1;
}

static void search_whole(SDC_t* sdc, u8* byteArr, u32 len, s32* blockIndex, s32* indexInBlock)
{
	for (u8 i = 0; i < 200; i++)
		trace_printf("#");
	trace_printf("\n");

	u8 successfull;

	/*	for every block in the SD-card	*/
	for (u32 i = 0; i < 8388608; i++)
	{
		/*	read block	*/
		successfull = SDC_u8ReadBlock(sdc, sdc->block, 0);
		if (!successfull)
		{
			//__asm volatile ("bkpt 0");
			//trace_printf("read failed. retrying\n");
			i--;
		}

		/*	search in block	*/
		*indexInBlock = find_in_block(sdc->block, 512, byteArr, len);
		if (*indexInBlock != -1)
		{
			*blockIndex = i;
			__asm volatile ("bkpt 0");
			return;
		}

		//trace_printf("%d\n", i);

		if (i % (83886 / 2) == 0)
		{
			//static s32 p = 0;
			//trace_printf("%d\n", p++);
			trace_printf("=");
		}
	}

	*indexInBlock = -1;
	*blockIndex = -1;
}

/*******************************************************************************
 * Stream:
 ******************************************************************************/
static SDC_DirRecordType_t get_dir_record_type(SDC_DirData_t* rec)
{
	u8 u8Attrib = *((u8*)&(rec->attrib));

	/*	Normal	*/
	if (!rec->attrib.volumeId  &&
		!rec->attrib.directory &&
		!rec->attrib.unused0   &&
		!rec->attrib.unused1
	)
		return SDC_DirRecordType_Normal;

	/*	Long file name	*/
	if (rec->attrib.system    &&
		rec->attrib.volumeId  &&
		rec->attrib.directory &&
		rec->attrib.archive   &&
		!rec->attrib.unused0  &&
		!rec->attrib.unused1
	)
		return SDC_DirRecordType_LongFileName;

	/*	unused	*/
	if (rec->shortFileName[0] == 0xE5)
		return SDC_DirRecordType_Unused;

	/*	End of directory	*/
	if (rec->shortFileName[0] == 0)
		return SDC_DirRecordType_EndOfDir;

	/*	Otherwise, unknown type	*/
	return SDC_DirRecordType_Unknown;
}

/*
 * Converts user written file name to a FAT32 understandable file name.
 * Example:
 * 		"file.nc" ==> "file    nc "
 */
static void get_in_file_name(char inFileName[11], char* fileName)
{
	/*	copy from first to the '.' or the end of "fileNme" if '.' does not exist	*/
	s8 dotIndex = -1;
	volatile u8 i = 0;
	for (; ; i++)
	{
		if (fileName[i] == '.')
		{
			dotIndex = i;
			break;
		}

		if (fileName[i] == '\0')
			break;

		inFileName[i] = toupper(fileName[i]);
	}

	/*	if '.' does not exist	*/
	if (dotIndex == -1)
	{
		/*	fill rest of "inFileName" with spaces	*/
		for (; i < 11; i++)
			inFileName[i] = ' ';
		/*	end function	*/
		return;
	}

	/*	otherwise, if '.' exists, add spaces until last 3 bytes	*/
	for (; i < 8; i++)
		inFileName[i] = ' ';

	/*	copy extension	*/
	for (i = 0; i < 3; i++)
	{
		if (fileName[dotIndex + 1 + i] == '\0')
			break;
		inFileName[8 + i] = toupper(fileName[dotIndex + 1 + i]);
	}

	/*	fill rest of "inFileName" with spaces (some extensions are of 1 or two bytes only)	*/
	for (; i < 3; i++)
		inFileName[8 + i] = ' ';
}

/*
 * Compares 11 bytes with 11 bytes
 */
static u8 are_equal_names(char* name1, char* name2)
{
	for (u8 i =0; i < 11; i++)
	{
		if (name1[i] != name2[i])
			return 0;
	}
	return 1;
}

ALWAYS_INLINE_STATIC u32 get_cluster_lba(SDC_t* sdc, u32 clusterNumber)
{
	return sdc->clustersBeginLba + (clusterNumber - 2) * sdc->sectorsPerCluster;
}

/*
 * Returns 0 if not found but containing directory has not yet ended.
 * Returns 1 if found.
 * Returns 2 if not found and containing directory has ended.
 */
static u8 find_dirData_in_current_sector(
	SDC_t* sdc, char* inFileName, SDC_DirData_t** dirDataPP)
{
	/*	List all files in the current sector and search for "inFileName" among them	*/
	for (u16 i = 0; i < 16; i++)
	{
		/*	get pointer to the i-th record	*/
		*dirDataPP = (SDC_DirData_t*)&(sdc->block[32 * i]);
		/*	get type of this record	*/
		SDC_DirRecordType_t recType = get_dir_record_type(*dirDataPP);
		/*	check for end of directory	*/
		if (recType == SDC_DirRecordType_EndOfDir)
			return 2;
		/*	check for short file name	*/
		if (recType != SDC_DirRecordType_Normal)
			continue;
		/*	if "dirData" record expresses a short named file, compare it with the given "fileName"	*/
		if (are_equal_names(inFileName, (*dirDataPP)->shortFileName))
			return 1;
	}

	return 0;
}

/*
 * Returns 0 if not found but containing directory has not yet ended.
 * Returns 1 if found.
 * Returns 2 if not found and containing directory has ended.
 */
static u8 find_dirData_in_cluster(
	SDC_t* sdc, char* inFileName, u32 clusterNumber, SDC_DirData_t** dirDataPP)
{
	u8 successfull;
	u8 found;

	/*	Get LBA of that cluster	*/
	u32 clusterLba = get_cluster_lba(sdc, clusterNumber);

	/*	For every sector in the cluster	*/
	for (u8 iSector = 0; iSector < sdc->sectorsPerCluster; iSector++)
	{
		/*	Read that sector into the buffer	*/
		successfull = SDC_u8ReadBlock(sdc, sdc->block, clusterLba + iSector);
		if (!successfull)
			return 0;

		/*	Search in this sector	*/
		found = find_dirData_in_current_sector(sdc, inFileName, dirDataPP);

		/*	if not found but containing directory has not yet ended	*/
		if (found == 0)
			continue;

		/*	if found	*/
		if (found == 1)
			return 1;

		/*	if not found and containing directory has ended	*/
		if (found == 2)
			return 2;
	}

	/*	Cluster ended and file has not been found, and also, directory has not yet ended	*/
	return 0;
}

static u32 get_next_cluster_number(SDC_t* sdc, u32 currentClusterNumber)
{
	u8 successfull;

	/*	Get next cluster number by reading FAT's integer indexed by "currentClusterNumber"	*/
	/*	Read FAT (File Allocation Table) sector containing that entry	*/
	successfull = SDC_u8ReadBlock(sdc, sdc->block, sdc->fat.lba + currentClusterNumber / 128);
	if (!successfull)
		return 0xFFFFFFFF;

	SDC_NextClusterEntry_t nextClusterEntry =
		((SDC_NextClusterEntry_t*)sdc->block)[currentClusterNumber % 128];

	/*	read data pointed to by the data entry	*/
	u32 nextClusterNumber = nextClusterEntry.indexInSector;

	/*	if there's no next cluster	*/
	u32 u32entry = ((u32*)sdc->block)[currentClusterNumber % 128];
	if (u32entry >= 0xFFFFFFF8 || u32entry == 0x0FFFFFFF)
		return 0xFFFFFFFF;

	/*	clear upper 4-bits	*/
	nextClusterNumber = nextClusterNumber & 0x0FFFFFFFF;

	return nextClusterNumber;
}

/*
 * Returns 0 if not found.
 * Returns 1 if found.
 */
static u8 find_dirData_in_directory(
	SDC_t* sdc, char* inFileName, u32 dirFirstClusterNumber, SDC_DirData_t** dirDataPP)
{
	u8 found;

	/*	For every cluster in the directory	*/
	u32 currentClusterNumber = dirFirstClusterNumber;
	while(currentClusterNumber != 0xFFFFFFFF)
	{
		/*	Search in this cluster	*/
		found = find_dirData_in_cluster(sdc, inFileName, currentClusterNumber, dirDataPP);

		/*	if found	*/
		if (found == 1)
			return 1;

		/*	if not found and containing directory has ended	*/
		if (found == 2)
			return 2;

		/*	Otherwise, if not found but containing directory has not yet ended	*/
		/*	get number of the next cluster	*/
		currentClusterNumber = get_next_cluster_number(sdc, currentClusterNumber);
	}

	/*	if directory clusters ended and still file has not been found	*/
	return 0;
}

/*	Gets cluster number of a cluster given its index, and first cluster number	*/
static u32 get_cluster_number(SDC_t* sdc, u32 firstClusterNumber, u32 clusterIndex)
{
	u32 clusterNumber = firstClusterNumber;
	for (u32 i = 0; i < clusterIndex; i++)
	{
		if (clusterNumber == 65)
		{
			__asm volatile ("bkpt 0");
		}
		clusterNumber = get_next_cluster_number(sdc, clusterNumber);
	}
	return clusterNumber;
}

u8 SDC_u8OpenStream(SD_Stream_t* stream, SDC_t* sdc, char* fileName)
{
	u8 successfull;
	SDC_DirData_t* dirData;
	volatile u8 found = 0;
	char inFileName[11];
	get_in_file_name(inFileName, fileName);

	stream->sdc = sdc;
	stream->reader = 0;

	/*	Search for file's directory data record in the root directory	*/
	found = find_dirData_in_directory(sdc, inFileName, 2, &dirData);

	/*	if not found (TODO: create it)	*/
	if (!found)
		return 0;

	/*	Get size of the found file	*/
	stream->sizeActual = dirData->fileSize;
	stream->sizeOnSDC = dirData->fileSize;

	/*	Get first cluster number of the found file	*/
	stream->firstClusterNumber =
		((u32)dirData->firstClusterHigh << 16) | (u32)dirData->firstClusterLow;

	/*	Get LBA of this cluster	*/
	u32 lba = get_cluster_lba(sdc, stream->firstClusterNumber);

	/*	read first sector of file's first cluster into stream object buffer	*/
	successfull = SDC_u8ReadBlock(sdc, stream->buffer, lba);
	if (!successfull)
		return 0;
	stream->bufferOffset = 0;

	/*	stream opened	*/
	return 1;
}

void SDC_voidKeepTryingOpenStream(SD_Stream_t* stream, SDC_t* sdc, char* fileName)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{
			successfull = SDC_u8OpenStream(stream, sdc, fileName);
			if (successfull)
				return;
		}

		while(!init_flow(sdc));
	}
}

/*	Saves sector that is currently in buffer into the SD-card	*/
static u8 save_current_buffer(SD_Stream_t* stream)
{
	volatile u8 successfull;

	/*	Get cluster index of the sector to be buffered	*/
	u32 clusterIndex = stream->bufferOffset / stream->sdc->sectorsPerCluster;

	/*	Get cluster number of this cluster index	*/
	u32 clusterNumber = get_cluster_number(stream->sdc, stream->firstClusterNumber, clusterIndex);
	if (clusterNumber == 0xFFFFFFFF)
		return 0;

	/*	Get LBA of the sector to be buffered	*/
	u32 lba =
		get_cluster_lba(stream->sdc, clusterNumber) +
		stream->bufferOffset  % stream->sdc->sectorsPerCluster;

	/*	Write the current buffer to the SD-card	*/
	successfull = SDC_u8WriteBlock(stream->sdc, stream->buffer, lba);
	if (!successfull)
		return 0;

	return 1;
}

/*	Reads sector from SD-card to stream's buffer	*/
static u8 read_sector(SD_Stream_t* stream, u32 sectorsOffset)
{
	u8 successfull;

	/*	Get cluster index of the sector to be buffered	*/
	u32 clusterIndex = sectorsOffset / stream->sdc->sectorsPerCluster;

	/*	Get cluster number of this cluster index	*/
	u32 clusterNumber = get_cluster_number(stream->sdc, stream->firstClusterNumber, clusterIndex);
	if (clusterNumber == 0xFFFFFFFF)
		return 0;

	/*	Get LBA of the sector to be buffered	*/
	u32 lba =
		get_cluster_lba(stream->sdc, clusterNumber) +
		sectorsOffset % stream->sdc->sectorsPerCluster;

	/*	Read that sector	*/
	successfull = SDC_u8ReadBlock(stream->sdc, stream->buffer, lba);
	if (!successfull)
		return 0;

	stream->bufferOffset = sectorsOffset;

	return 1;
}

/*
 * If the requested byte offset is outside stream's buffer, the buffer is saved
 * to the SD-card, and the sector containing the requested byte offset is copied
 * to stream's buffer.
 *
 * Returns 1 if successful, 0 otherwise.
 */
static u8 update_buffer(SD_Stream_t* stream, u32 offset)
{
	u8 successfull;

	/*	if the given offset is outside the sector currently in buffer	*/
	u32 sectorsOffset = offset / 512;
	if (sectorsOffset != stream->bufferOffset)
	{
		/*	save the current buffer to SD-card	*/
		successfull = save_current_buffer(stream);
		if (!successfull)
			return 0;

		/*	Read new buffer from SD-card	*/
		successfull = read_sector(stream, sectorsOffset);
		if (!successfull)
			return 0;
	}

	return 1;
}

static void keep_trying_update_buffer(SD_Stream_t* stream, u32 offset)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{
			successfull = update_buffer(stream, offset);
			if (successfull)
				return;
		}

		while(!init_flow(stream->sdc));
	}
}

u8 SDC_u8ReadStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len)
{
	u8 successfull;

	/*
	 * Program will copy from "stream->buffer" and break when it reaches its end,
	 * then, if the required length is not yet copied, an "update_buffer()" operation
	 * will take place before continuing.
	 */
	u32 i = 0;
	while(1)
	{
		if (i == len)
			return 1;

		if ((offset+i) % 512 == 0)
		{
			successfull = update_buffer(stream, offset+i);
			if (!successfull)
				return 0;
		}

		arr[i] = stream->buffer[(offset+i) % 512];
		i++;
	}
}

void SDC_voidKeepTryingReadStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{

			successfull = SDC_u8ReadStream(stream, offset, arr, len);
			if (successfull)
				return;
			extern u32 numberOfFails;
			numberOfFails++;
		}

		while(!init_flow(stream->sdc));
	}
}

u8 SDC_u8WriteStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len)
{
	/*	TODO: if written with more than original size, update size field in the data record on the card	*/
	u8 successfull;

	/*
	 * Program will copy to "stream->buffer" and break when it reaches its end,
	 * then, if the required length is not yet copied, an "update_buffer()" operation
	 * will take place before continuing.
	 */
	u32 i = 0;
	while(1)
	{
		if (i == len)
			return 1;

		if ((offset+i) % 512 == 0)
		{
			successfull = update_buffer(stream, offset+i);
			if (!successfull)
				return 0;
		}

		stream->buffer[(offset+i) % 512] = arr[i];
		i++;
	}
}

void SDC_voidKeepTryingWriteStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{
			successfull = SDC_u8WriteStream(stream, offset, arr, len);
			if (successfull)
				return;
			extern u32 numberOfFails;
			numberOfFails++;
		}

		while(!init_flow(stream->sdc));
	}
}

u8 SDC_u8SaveStream(SD_Stream_t* stream)
{
	u8 successfull;

	/*	save the current buffer to SD-card	*/
	successfull = save_current_buffer(stream);
	if (!successfull)
		return 0;

	return 1;
}

void SDC_voidKeepTryingSaveStream(SD_Stream_t* stream)
{
	u8 successfull;

	while(1)
	{
		for (u8 i = 0; i < 3; i++)
		{
			successfull = SDC_u8SaveStream(stream);
			if (successfull)
				return;
		}

		while(!init_flow(stream->sdc));
	}
}

void SDC_voidGetNextLine(SD_Stream_t* stream, char* line, u32 maxSize)
{
	u32 offset = stream->reader;
	u8 i = 0;
	while(1)
	{
		/*	if max size is reached, or stream file has ended	*/
		if ( (i >= maxSize) || (offset+i >= stream->sizeActual) )
		{
			line[i] = '\0';
			stream->reader = offset + i;
			return;
		}

		/*	if going to start reading from next sector, update buffer	*/
		if ((offset+i) % 512 == 0)
			keep_trying_update_buffer(stream, offset+i);

		/*	Copy byte	*/
		line[i] = stream->buffer[(offset+i) % 512];

		/*	check end of line	*/
		if (line[i] == '\n')
		{
			if (i > 0)
			{
				if (line[i - 1] == '\r')	// remove unnecessary '\r'
					line[i - 1] = '\0';
			}
			line[i] = '\0';
			stream->reader = offset + i + 1;
			return;
		}

		i++;
	}
}

void SDC_voidResetLineReader(SD_Stream_t* stream)
{
	stream->reader = 0;
}

u8 SDC_u8IsThereNextLine(SD_Stream_t* stream)
{
	return (stream->reader < stream->sizeActual);
}






