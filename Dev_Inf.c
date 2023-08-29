/*********************************************
 * @file Dev_Inf.c
 * @brief modified by Mauro linking W25Qxxx library
 * @date: 01 august 2023
 * @version V.1.0.0
 * 
 *********************************************
 * Creating an new External loader you have to 
 * configure the first and the third field in 
 * below struct. Setup also Loader_Src.c
 *********************************************/

#include "main.h"
#include "Dev_Inf.h"
#include "z_flash_W25QXXX.h"


/* This structure containes information used by ST-LINK Utility to program and erase the device */
#if defined (__ICCARM__)
__root struct StorageInfo const StorageInfo  =  {
#else
struct StorageInfo const StorageInfo  =  {
#endif
   "W25Q80_BLACKPILL-F411_LED", 	 	 		// Device Name + version number
   SPI_FLASH,                  					// Device Type  (that's from Dev_Inf.h)
   0x90000000,                					// Device Start Address
   EXT_FLASH_SIZE,                 				// Device Size in Bytes (that's from Flash interface package)
   EXT_FLASH_PAGE_SIZE,                 		// Programming Page Size (that's from Flash interface package)
   0xFF,                       					// Initial Content of Erased Memory
// Specify Size and Address of Sectors (view example below)
   EXT_FLASH_PAGE_NUM, EXT_FLASH_SECTOR_SIZE,	// (that's from Flash interface package)
   0x00000000, 0x00000000,
};

/*  								Sector coding example
	A device with succives 16 Sectors of 1KBytes, 128 Sectors of 16 KBytes, 
	8 Sectors of 2KBytes and 16384 Sectors of 8KBytes
	
	0x00000010, 0x00000400,     							// 16 Sectors of 1KBytes
	0x00000080, 0x00004000,     							// 128 Sectors of 16 KBytes
	0x00000008, 0x00000800,     							// 8 Sectors of 2KBytes
	0x00004000, 0x00002000,     							// 16384 Sectors of 8KBytes
	0x00000000, 0x00000000,								// end
  */
