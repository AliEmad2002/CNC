/*
 * SDC_CRC.h
 *
 *  Created on: Apr 26, 2023
 *      Author: Ali Emad
 */

#ifndef INCLUDE_HAL_SDC_SDC_CRC_H_
#define INCLUDE_HAL_SDC_SDC_CRC_H_


/*
 * The following table was generated using the code commented below:
 *
 *
 *		#include <stdio.h>
 *
 *		typedef unsigned char u8;
 *
 *		#define MSB(x) (x >> 7)
 *
 *		u8 p = 0x89;
 *
 *		u8 get_crc(u8 x)
 *		{
 *			u8 c = x;
 *			if (MSB(c) == 1)
 *				c = c ^ p;
 *
 *			for (u8 i = 0; i < 7; i++)
 *			{
 *				c = c << 1;
 *				if (MSB(c) == 1)
 *					c = c ^ p;
 *			}
 *
 *			return c;
 *		}
 *
 *		int main() {
 *			for (int i = 0; i < 256; i++)
 *			{
 *				printf("%d, ", get_crc(i));
 *				if ((i+1) % 4 == 0)
 *					printf("\n");
 *			}
 *
 *			return 0;
 *		}
 */

const u8 crcTable[256] = {
	0, 9, 18, 27,
	36, 45, 54, 63,
	72, 65, 90, 83,
	108, 101, 126, 119,
	25, 16, 11, 2,
	61, 52, 47, 38,
	81, 88, 67, 74,
	117, 124, 103, 110,
	50, 59, 32, 41,
	22, 31, 4, 13,
	122, 115, 104, 97,
	94, 87, 76, 69,
	43, 34, 57, 48,
	15, 6, 29, 20,
	99, 106, 113, 120,
	71, 78, 85, 92,
	100, 109, 118, 127,
	64, 73, 82, 91,
	44, 37, 62, 55,
	8, 1, 26, 19,
	125, 116, 111, 102,
	89, 80, 75, 66,
	53, 60, 39, 46,
	17, 24, 3, 10,
	86, 95, 68, 77,
	114, 123, 96, 105,
	30, 23, 12, 5,
	58, 51, 40, 33,
	79, 70, 93, 84,
	107, 98, 121, 112,
	7, 14, 21, 28,
	35, 42, 49, 56,
	65, 72, 83, 90,
	101, 108, 119, 126,
	9, 0, 27, 18,
	45, 36, 63, 54,
	88, 81, 74, 67,
	124, 117, 110, 103,
	16, 25, 2, 11,
	52, 61, 38, 47,
	115, 122, 97, 104,
	87, 94, 69, 76,
	59, 50, 41, 32,
	31, 22, 13, 4,
	106, 99, 120, 113,
	78, 71, 92, 85,
	34, 43, 48, 57,
	6, 15, 20, 29,
	37, 44, 55, 62,
	1, 8, 19, 26,
	109, 100, 127, 118,
	73, 64, 91, 82,
	60, 53, 46, 39,
	24, 17, 10, 3,
	116, 125, 102, 111,
	80, 89, 66, 75,
	23, 30, 5, 12,
	51, 58, 33, 40,
	95, 86, 77, 68,
	123, 114, 105, 96,
	14, 7, 28, 21,
	42, 35, 56, 49,
	70, 79, 84, 93,
	98, 107, 112, 121
};


#endif /* INCLUDE_HAL_SDC_SDC_CRC_H_ */
