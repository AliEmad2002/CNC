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

/*	SD-Card	*/
typedef struct{
	SPI_UnitNumber_t spiUnitNumber;
	u8 csPin  : 4;
	u8 csPort : 4;
	SDC_Version_t ver;
	u8 crcEnabled;
}SDC_t;

typedef struct{

}SD_Stream_t;

/*
 * Initializes connection with the SD-card object.
 * (Notice that SysTick elapsed time counter MUST be enabled)
 */
void SDC_voidInitConnection(
	SDC_t* sdc, u8 crcEnable,
	SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap);

/*
 * Writes data block (512 bytes) in the SD-card.
 * Returns 1 if written successfully, 0 otherwise.
 */
u8 SDC_u8WriteBlock(SDC_t* sdc, u8* block, u32 blockNumber);

/*
 * Reads data block (512 bytes) from the SD-card.
 * Returns 1 if read successfully, 0 otherwise.
 */
u8 SDC_u8ReadBlock(SDC_t* sdc, u8* block, u32 blockNumber);

/*
 * Opens file from the SD card on a stream object.
 * Returns 1 if successfully opened. 0 otherwise.
 */
u8 SDC_u8OpenStream(SD_Stream_t* stream, SDC_t* sdc, char* fileDir);

/*	reads array of bytes from stream object	*/
void SDC_voidRead(SD_Stream_t* stream, u32 offset, u8* arr, u32 len);

/*	writes array of bytes to stream object	*/
void SDC_voidWrite(SD_Stream_t* stream, u32 offset, u8* arr, u32 len);

/*	Reads next un-read line of an opened text (non-binary formatted) file	*/
void SDC_voidNextLine(SD_Stream_t* stream, char* line);

/*	Resets line reader offset	*/
void SDC_voidResetLineReader(SD_Stream_t* stream);

/*	Checks if there's a next line	*/
u8 SDC_u8IsThereNextLine(SD_Stream_t* stream);

/*	saves changes made on stream object	*/
void SDC_voidSave(SD_Stream_t* stream);



#endif /* INCLUDE_HAL_SDC_SDC_INTERFACE_H_ */
