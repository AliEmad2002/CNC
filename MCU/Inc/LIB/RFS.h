/*
 * RFS.h (Record File System)
 *
 *  Created on: Apr 23, 2023
 *      Author: Ali Emad
 */

#ifndef INCLUDE_LIB_RFS_H_
#define INCLUDE_LIB_RFS_H_

typedef struct{
	u32 objSize;
}RFS_t;

/*
 * Copies object data stored in "rfs[index]" (on SD-card for example) to the RAM
 * location "objPtr".
 *
 * "objPtr" must be casted to (u8*) when passed to this function.
 */
void RFS_voidGetObject(u8* objPtr, RFS_t* rfs, u32 index);

/*	reverse of the previous function	*/
void RFS_voidStoreObject(u8* objPtr, RFS_t* rfs, u32 index);

/*	returns 1 if the given index exists in the "rfs". 0 otherwise	*/
u8 RFS_u8IndexExists(RFS_t* rfs, u32 index);




#endif /* INCLUDE_LIB_RFS_H_ */
