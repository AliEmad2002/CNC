/*
 * SDC_interface.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Ali Emad
 */

#ifndef INCLUDE_HAL_SDC_SDC_INTERFACE_H_
#define INCLUDE_HAL_SDC_SDC_INTERFACE_H_

#include "SPI_interface.h"
#include "GPIO_interface.h"

/*	SD-Card version	*/
typedef enum{
	SDC_Version_Unknown,
	SDC_Version_3,
	SDC_Version_2_ByteAddress,
	SDC_Version_2_BlockAddress,
	SDC_Version_1
}SDC_Version_t;

/*	File Allocation Table	*/
typedef struct{
	u32 lba;			  // LBA of the File Allocation Table.
	u32 sectorsPerFat;	  // Number of sectors of the File Allocation Table.
}SDC_FAT_t;

/*	SD-Card	*/
typedef struct{
	SPI_UnitNumber_t spiUnitNumber;

	u8 csPin  : 4;
	u8 csPort : 4;

	u8 rstPin  : 4;
	u8 rstPort : 4;

	SDC_Version_t ver;

	u8 crcEnabled;

	u8 block[512];
	u32 lbaRead; // LBA of the sector currently available in "block"

	SDC_FAT_t fat;

	u32 clustersBeginLba; // LBA of first root directory cluster in SD-card's partition.

	u8 sectorsPerCluster;
}SDC_t;

/*	Stream	*/
typedef struct{
	SDC_t* sdc;

	u32 sizeOnSDC;		// in bytes.
	u32 sizeActual;		// in bytes.

	u32 firstClusterNumber;	// First cluster number of the opened file.
	u8 buffer[512];
	u32 bufferOffset;	// offset of "buffer" from the sector of the opened file. unit is (sectors).
}SD_Stream_t;

/**
 * Following, all functions named starting by "keepTrying" would do the same functionality
 * of their previous ones, except that these function would do the following loop infinitely:
 * 		-	Try the function with a maximum of three chances of failure.
 * 		-	If the function still fails three times, reset the SD-card.
 **/

/*
 * Initializes connection with the SD-card object.
 * (Notice that SysTick elapsed time counter MUST be enabled)
 */
u8 SDC_u8InitConnection(
	SDC_t* sdc, u8 crcEnable,
	SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap);

void SDC_voidKeepTryingInitConnection(
	SDC_t* sdc, u8 crcEnable,
	SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap);

/*
 * Initializes SD-card's partition data. TTo be ready for "SD_Stream" use.
 * (Assumes the card has only one partition. if more, it takes the first)
 *
 * Returns 1 if initialized successfully, 0 otherwise.
 */
u8 SDC_u8InitPartition(SDC_t* sdc);

void SDC_voidKeepTryingInitPartition(SDC_t* sdc);

/*
 * Writes data block (512 bytes) in the SD-card.
 * Returns 1 if written successfully, 0 otherwise.
 */
u8 SDC_u8WriteBlock(SDC_t* sdc, u8* block, u32 blockNumber);

void SDC_voidKeepTryingWriteBlock(SDC_t* sdc, u8* block, u32 blockNumber);

/*
 * Reads data block (512 bytes) from the SD-card.
 * Returns 1 if read successfully, 0 otherwise.
 */
u8 SDC_u8ReadBlock(SDC_t* sdc, u8* block, u32 blockNumber);

void SDC_voidKeepTryingReadBlock(SDC_t* sdc, u8* block, u32 blockNumber);

/*
 * Opens file from the SD card on a stream object.
 * Returns 1 if successfully opened. 0 otherwise.
 *
 * TODO:
 * 		-	So-far, this driver can only access root directory files. Make it
 * 			access files from any directory.
 * 		-	So far, this driver can only open and modify already existing files.
 * 		-	So far, this driver can not allocate new clusters to the opened file,
 * 			so make sure it initially has enough allocated size.
 */
u8 SDC_u8OpenStream(SD_Stream_t* stream, SDC_t* sdc, char* fileName);

void SDC_voidKeepTryingOpenStream(SD_Stream_t* stream, SDC_t* sdc, char* fileName);

/*	reads array of bytes from stream object	*/
/* TODO: add functions that get and set by reference (They are only guaranteed until next buffer update!)*/
u8 SDC_u8ReadStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len);

void SDC_voidKeepTryingReadStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len);

/*	writes array of bytes to stream object	*/
u8 SDC_u8WriteStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len);

void SDC_voidKeepTryingWriteStream(SD_Stream_t* stream, u32 offset, u8* arr, u32 len);

/*	Closes / Saves stream	*/
u8 SDC_u8SaveStream(SD_Stream_t* stream);

void SDC_voidKeepTryingSaveStream(SD_Stream_t* stream);

/*	Reads next un-read line of an opened text (non-binary formatted) file	*/
void SDC_voidNextLine(SD_Stream_t* stream, char* line);

/*	Resets line reader offset	*/
void SDC_voidResetLineReader(SD_Stream_t* stream);

/*	Checks if there's a next line	*/
u8 SDC_u8IsThereNextLine(SD_Stream_t* stream);

/*	saves changes made on stream object	*/
void SDC_voidSave(SD_Stream_t* stream);



#endif /* INCLUDE_HAL_SDC_SDC_INTERFACE_H_ */
