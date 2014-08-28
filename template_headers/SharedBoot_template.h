/*
 * Shared_Boot.h
 *
 *  Created on: Dec 21, 2013
 *      Author: Nathan
 */

#ifndef SHARED_BOOT_H_
#define SHARED_BOOT_H_

/*
 * This routine fetches a 32-bit value from the peripheral
 * input stream.
 */
Uint32 GetLongData();

/**
 * This routine copies multiple blocks of data from the host
 * to the specified RAM locations.  There is no error
 * checking on any of the destination addresses.
 * That is it is assumed all addresses and block size
 * values are correct.
 *
 * Multiple blocks of data are copied until a block
 * size of 00 00 is encountered.
 */
void   CopyData(void);

/*
 * This function reads 8 reserved words in the header.
 * None of these reserved words are used by the
 * this boot loader at this time, they may be used in
 * future devices for enhancments.  Loaders that use
 * these words use their own read function.
 */
void ReadReservedFn(void);


#endif /* SHARED_BOOT_H_ */
