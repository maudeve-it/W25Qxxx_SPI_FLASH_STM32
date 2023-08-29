/*********************************************
 * @file Z_FLASH_W25QXXX.h
 * @author mauro
 * @date: 01 august 2023
 * @version V.1.0.0
 * 
 *********************************************
 * this version of library uses just polling 
 * mode transmission
 * this version of library uses standard SPI
 *********************************************
 * configure below STEP1 and STEP4.
 * Do not change STEP2 and STEP3 in this version
 *********************************************/

#ifndef INC_Z_FLASH_W25QXXX_H_
#define INC_Z_FLASH_W25QXXX_H_



/*||||||||||| USER/PROJECT PARAMETERS |||||||||||*/

/******************    STEP 1    ******************
 **************** PORT PARAMETERS *****************
 ** properly set the below th 2 defines to address
 ********  the SPI port defined on CubeMX *********
 **************************************************/
#define FLASH_SPI_PORT 	hspi1
#define FLASH_SPI 		SPI1


/******************    STEP 2    *******************
 **************** FLASH READING MODE ***************
 **** FLASH_MODE 1	->	Fast mode
 **** FLASH_MODE 2	->	Dual mode // NOT IMPLEMENTED
 **** FLASH_MODE 4	->	Quad mode // NOT IMPLEMENTED
 **** otherwise		->	Standard Mode (warning: standard mode not available if SPO port speed is above 50 MHZ)
 **** SPI port must be previously correctly defined via CubeMX
 **************************************************/
#define EXT_FLASH_MODE 		1



/*****************     STEP 3      *****************
 ************* SPI COMMUNICATION MODE **************
 *** enable SPI mode want, uncommenting ONE row ****
 **** (Setup the same configuration on CubeMX) *****
 ***************************************************/
#define EXT_FLASH_SPI_POLLING_MODE
//#define EXT_FLASH_SPI_DMA_MODE // (mixed: polling/DMA, see below) NOT IMPLEMENTED



/*****************     STEP 4      *****************
 *********** set below information as per *************
 ********* chip memory used in the project *********
 ***************************************************/
/* active information */
#define EXT_FLASH_PAGE_SIZE		0x0100		//256b 		page size (bits)
#define EXT_FLASH_SECTOR_SIZE	0x1000		//4kB 		sector size (bytes)
#define EXT_FLASH_BLOCK_SIZE	0x00010000	//64kB 		block size (bytes)
#define EXT_FLASH_SIZE			0X00100000	//1MB-8Mb	total size (bytes)
#define EXT_FLASH_PAGE_NUM		0x1000		//4096 		pages
#define EXT_FLASH_SECTOR_NUM	0x0100		//256 		sectors
#define EXT_FLASH_BLOCK_NUM		0x0010		//16 		blocks


/* here values for the W25Q80DV/DL chips
#define EXT_FLASH_PAGE_SIZE		0x0100		//256b 		page size (bits)
#define EXT_FLASH_SECTOR_SIZE	0x1000		//4kB 		sector size (bytes)
#define EXT_FLASH_BLOCK_SIZE	0x00010000	//64kB 		block size (bytes)
#define EXT_FLASH_SIZE			0X00100000	//1MB-8Mb	total size (bytes)
#define EXT_FLASH_PAGE_NUM		0x1000		//4096 		pages
#define EXT_FLASH_SECTOR_NUM	0x0100		//256 		sectors
#define EXT_FLASH_BLOCK_NUM		0x0010		//16 		blocks
*/

/* here values for the W25Q64JV chips
#define EXT_FLASH_PAGE_SIZE		0x0100		//256b 		page size (bits)
#define EXT_FLASH_SECTOR_SIZE	0x1000		//4kB 		sector size (bytes)
#define EXT_FLASH_BLOCK_SIZE	0x00010000	//64kB 		block size (bytes)
#define EXT_FLASH_SIZE			0X00800000	//8MB-64Mb	total size (bytes)
#define EXT_FLASH_PAGE_NUM		0x8000		//32768		pages
#define EXT_FLASH_SECTOR_NUM	0x0800		//2048 		sectors
#define EXT_FLASH_BLOCK_NUM		0x0080		//128		blocks
*/

/* here values for the W25Q128JV chips
#define EXT_FLASH_PAGE_SIZE		0x0100		//256b 		page size (bits)
#define EXT_FLASH_SECTOR_SIZE	0x1000		//4kB 		sector size (bytes)
#define EXT_FLASH_BLOCK_SIZE	0x00010000	//64kB 		block size (bytes)
#define EXT_FLASH_SIZE			0X01000000	//16MB-128Mb	total size (bytes)
#define EXT_FLASH_PAGE_NUM		0x00010000	//32768		pages
#define EXT_FLASH_SECTOR_NUM	0x1000		//4096 		sectors
#define EXT_FLASH_BLOCK_NUM		0x0100		//256		blocks
*/




#define EXT_FLASH_DMA_CUTOFF	20			//that's related to uC DMA and SPI. You can leave it unchanged

/*|||||||| END OF USER/PROJECT PARAMETERS ||||||||*/




/*||||||||||||||| DEVICE PARAMETERS ||||||||||||||||||*/
// W25QXX EEPROM family commands

#define W25_RESET_EN		0x66	//sequence is 0x66 + 0x99 + 30us delay
#define W25_RESET			0x99 	//sequence is 0x66 + 0x99 + 30us delay
#define W25_W_ENABLE		0x06
#define W25_READ 			0x03
#define W25_FREAD 			0x0B
#define W25_FREAD_DUAL		0x3B
#define W25_FREAD_QUAD		0x6B
#define W25_PAGE_P 			0x02
#define W25_S_ERASE4K 		0x20
#define W25_B_ERASE32K		0x52
#define W25_B_ERASE64K		0xD8
#define W25_CH_ERASE		0xC7
#define W25_POWERDOWN		0xB9
#define W25_POWERUP_ID		0xAB
#define W25_JEDEC_ID		0x9F
#define W25_R_SR1			0x05
#define W25_R_SFPD_REG		0x5A

/* unused commands
#define W25_SR_W_ENABLE		0x50
#define W25_W_DISABLE		0x04
#define W25_DEVICE_ID		0x90
#define W25_UNIQUE_ID		0x4B
#define W25_FREAD_DUAL_IO	0xBB
#define W25_FREAD_QUAD_IO	0xEB
#define W25_EP_SUS	 		0x75
#define W25_EP_RES	 		0x7A
#define W25_W_SR1			0x01
#define W25_R_SR2			0x35
#define W25_W_SR2			0x31
#define W25_R_SR3			0x15
#define W25_W_SR3			0x11
#define W25_R_SFPD_REG		0x5A
#define W25_E_SEC_REG		0x44
#define W25_P_SEC_REG		0x42
#define W25_R_SEC_REG		0x48
#define W25_G_BL_LOCK		0x7E
#define W25_G_BL_UNLK		0x98
#define W25_R_BL_LOCK		0x3D
#define W25_I_BL_LOCK		0x36
#define W25_I_BL_UNLK		0x39
#define W25_EP_SUSPEND		0x75
#define W25_EP_RESUME		0x75
 end of unused commands */
// W25QXX EEPROM family commands

#define W25_DUMMY			0x00	//dummy MUST be 0x00, in "read manufacturer"

// bit masks of W25QXX SR1, SR2, SR3 registers
#define SR1_BIT_BUSY		(01U)  //status only: 1 means busy device

/* unused bitmasks
#define SR1_BIT_WEL			(02U)  //status only: 1 means write enabled. set by W25_W_ENABLE command
#define SR1_BIT_BP0			(04U)  //writable: block protect bit 0
#define SR1_BIT_BP1			(08U)  //writable: block protect bit 1
#define SR1_BIT_BP2			(10U)  //writable: block protect bit 2
#define SR1_BIT_TB			(20U)  //writable: top(=1)/bottom(=0) starting, block protection bit
#define SR1_BIT_SEC			(40U)  //writable: sector(4kb)/block(64kb) block protection (1=sector)
#define SR1_BIT_SRP			(80U)  //writable: set SR registers protection (together with SRL)
#define SR2_BIT_SRL			(01U)  //writable: set SR registers protection (together with SRL)
#define SR2_BIT_QE			(02U)  //writable: enable (=1) QUAD SPI mode. if =0 SPI is Standard/Dual
#define SR2_BIT_LB1			(08U)  //OTP: 1 means Security Register 1 is permanently set readonly
#define SR2_BIT_LB2			(10U)  //OTP: 1 means Security Register 2 is permanently set readonly
#define SR2_BIT_LB3			(20U)  //OTP: 1 means Security Register 3 is permanently set readonly
#define SR2_BIT_CMP			(40U)  //writable: complement protect: reverse protection of BP0-1-2,TB,SEC
#define SR2_BIT_SUS			(80U)  //writable: suspend status: 1 indicates erase/program suspended
#define SR3_BIT_WPS			(04U)  //writable: Write protect scheme: 1=using individual block flag, 0=using BPx, etc, flags
#define SR3_BIT_DRV0		(20U)  //writable: sets output driver strength
#define SR3_BIT_DRV1		(40U)  //writable: sets output driver strength
 end of W25QXX SR1, SR2, SR3 registers bitmasks */


#if FLASH_MODE == 1
	#define FLASH_READ_COMMAND	 W25_FREAD
#elif FLASH_MODE == 2
	#define FLASH_READ_COMMAND	 W25_FREAD_DUAL
#elif FLASH_MODE == 4
	#define FLASH_READ_COMMAND	 W25_FREAD_QUAD
#else
	#define FLASH_READ_COMMAND	 W25_READ
#endif



/*||||||||||| END OF DEVICE PARAMETERS ||||||||||||*/


void 	 Flash_Read(uint32_t addr, uint8_t* data, uint32_t dataSize);
void 	 Flash_Write(uint32_t addr, uint8_t* data, uint32_t dataSize);
//void 	 Flash_WaitForWritingComplete();
void 	 Flash_SErase4k(uint32_t addr);
void 	 Flash_BErase32k(uint32_t addr);
void 	 Flash_BErase64k(uint32_t addr);
void 	 Flash_ChipErase();
void 	 Flash_PowerDown();
uint8_t  Flash_ReadDevID();
uint16_t Flash_ReadManufactutrerAndDevID();
uint32_t Flash_ReadJedecID();
void 	 Flash_ReadSFDP(uint8_t* data);
void 	 Flash_Reset();
uint8_t  Flash_Init();	//initialization: includes availability test and reset
void 	 DataReader_WaitForReceiveDone();
void 	 DataReader_ReadData(uint32_t address24, uint8_t* buffer, uint32_t length);
void 	 DataReader_StartDMAReadData(uint32_t address24, uint8_t* buffer, uint32_t length);





#endif /* INC_Z_FLASH_W25QXXX_H_ */
