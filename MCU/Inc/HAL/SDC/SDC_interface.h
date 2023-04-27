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

/*	SD-Card	*/
typedef struct{
	SPI_UnitNumber_t spiUnitNumber;
	u8 csPin  : 4;
	u8 csPort : 4;
}SDC_t;

/*	Responses	*/
typedef struct{
	u8 inIdleState   : 1;
	u8 eraseRst      : 1;
	u8 illigalCmdErr : 1;
	u8 cmdCrcErr     : 1;
	u8 eraseSeqErr   : 1;
	u8 addressErr    : 1;
	u8 parameterErr  : 1;
	u8 startBit      : 1;		// always received 0
}SDC_R1_t;

typedef struct{

}SDC_R2_t;

typedef struct{

}SDC_R3_t;

typedef struct{
	u8 checkPattern     : 8;
	u8 voltageAccepted  : 4;
	u8 reserved0        : 4;
	u8 reserved1        : 4;
	u8 reserved2        : 4;
	u8 reserved3        : 4;
	u8 commandVersion   : 4;
	SDC_R1_t r1;
}SDC_R7_t;

typedef enum{

}SDC_Version_t;

typedef struct{

}SD_Stream_t;

/*
 * Initializes connection with the SD-card object.
 */
void SDC_voidInitConnection(
	SDC_t* sdc, SPI_UnitNumber_t spiUnitNumber, GPIO_Pin_t csPin, u8 afioMap);

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
