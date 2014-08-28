// TI File $Revision: /main/1 $
// Checkin $Date: January 22, 2009   16:48:37 $
//###########################################################################
//
// FILE:    Shared_Boot.c
//
// TITLE:   Boot loader shared functions
//
// Functions:
//
//     void   CopyData(void)
//     Uint32 GetLongData(void)
//     void ReadReservedFn(void)
//
//###########################################################################
// $TI Release: TMS320x2803x Boot ROM V1.0 $
// $Release Date: January 22, 2009 $
//###########################################################################


#include "boot_template.h"
#include "SharedBoot_template.h"
#include "Flash2803x_API_Library.h"

/*
	COMMENTED OUT FOR TEMPLATE CHECK IF THIS WORKS
	#pragma    DATA_SECTION(EmuKey,"EmuKeyVar");
	#pragma    DATA_SECTION(EmuBMode,"EmuBModeVar");
	Uint16     EmuKey;
	Uint16     EmuBMode;
*/

// GetWordData is a pointer to the function that interfaces to the peripheral.
// Each loader assigns this pointer to it's particular GetWordData function.
uint16fptr GetWordData;

FLASH_ST FlashStatus;

// Function prototypes


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
void CopyData()
{


   struct HEADER {
     Uint16 BlockSize;
     Uint32 DestAddr;
   } BlockHeader;

   Uint16 wordData;
   Uint16 i;
   Uint16  Status;


   // Get the size in words of the first block
   BlockHeader.BlockSize = (*GetWordData)();

   // While the block size is > 0 copy the data
   // to the DestAddr.  There is no error checking
   // as it is assumed the DestAddr is a valid
   // memory location

   while(BlockHeader.BlockSize != (Uint16)0x0000)
   {
      BlockHeader.DestAddr = GetLongData();
      for(i = 1; i <= BlockHeader.BlockSize; i++)
      {
          wordData = (*GetWordData)();
          if (BlockHeader.DestAddr < BOOTSTART || BlockHeader.DestAddr >= BOOTEND) //DON'T PROGRAM IN BOOT FLASH!
          {
        	  Status = Flash_Program((Uint16*)BlockHeader.DestAddr,&wordData,1,&FlashStatus);
          }
          BlockHeader.DestAddr++;
      }

      // Get the size of the next block
      BlockHeader.BlockSize = (*GetWordData)();
   }
   return;
}

Uint32 GetLongData()
{
    Uint32 longData;

    // Fetch the upper 1/2 of the 32-bit value
    longData = ( (Uint32)(*GetWordData)() << 16);

    // Fetch the lower 1/2 of the 32-bit value
    longData |= (Uint32)(*GetWordData)();

    return longData;
}

void ReadReservedFn()
{
    Uint16 i;
    // Read and discard the 8 reserved words.
    for(i = 1; i <= 8; i++)
    {
       GetWordData();
    }
    return;
}
