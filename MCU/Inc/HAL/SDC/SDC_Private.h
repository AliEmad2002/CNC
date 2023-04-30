/*
 * SDC_Private.h
 *
 *  Created on: Apr 28, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_HAL_SDC_SDC_PRIVATE_H_
#define INCLUDE_HAL_SDC_SDC_PRIVATE_H_

/*
 * SD-Card's OCR register.
 * (defined in p161 of the doc: Physical Layer Simplified Specification Version 6.00)
 */
typedef struct{
	u32 vddVoltageWindow : 24;
	u32 switchAccepted   : 1;
	u32 reserved         : 4;
	u32 uhs              : 1;
	u32 ccs              : 1;
	u32 busy             : 1;
}SDC_OCR_t;

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
	SDC_OCR_t ocr;
	SDC_R1_t r1;
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

typedef struct{
	u8 startBit : 1;
	u8 accepted : 1;
	u8 crcErr   : 1;
	u8 wrtErr   : 1;
	u8 endBit   : 1;
}SDC_Data_Response_t;

typedef struct{
	u8 bootFlag;
	u32 chsBegin : 24;
	u8 typeCode;
	u32 chsEnd : 24;
	u32 lbaBegin;
	u32 numberOfSectors;
}SDC_Partition_Entry_t;

typedef struct{
	u8 readOnly  : 1;
	u8 hidden    : 1;
	u8 system    : 1;
	u8 volumeId  : 1;
	u8 directory : 1;
	u8 archive   : 1;
	u8 unused0   : 1;
	u8 unused1   : 1;
}SDC_DirAttrib_t;

typedef struct{
	char shortFileName[11];
	SDC_DirAttrib_t attrib;
	u32 reserved0[2];
	u16 firstClusterHigh;
	u16 reserved1;
	u16 reserved2;
	u16 firstClusterLow;
	u32 fileSize;
}SDC_DirData_t;

typedef enum{
	SDC_DirRecordType_Normal,
	SDC_DirRecordType_LongFileName,
	SDC_DirRecordType_Unused,
	SDC_DirRecordType_EndOfDir,
	SDC_DirRecordType_Unknown
}SDC_DirRecordType_t;

typedef struct{
	u32 indexInSector : 7;  // Index of the 32-bit integer in the sector (described next),
							// which contain next cluster number.

	u32 sectorNumber  : 25; // Number of the sector of the File Allocation
							// Table (FAT) in which next cluster number is written.
}SDC_NextClusterEntry_t;












#endif /* INCLUDE_HAL_SDC_SDC_PRIVATE_H_ */
