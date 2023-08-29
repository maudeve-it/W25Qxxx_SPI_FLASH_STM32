/*********************************************
 * @file Z_FLASH_W25QXXX.c
 * @author mauro
 * @date: 01 august 2023
 * @version V.1.0.0
 * 
 *********************************************
 * this version of library uses just polling 
 * mode transmission
 * this version of library uses standard SPI
 *********************************************
 * it needs Z_FLASH_W25QXXX.h configuration
 *********************************************/


#include "main.h"
#include "z_flash_W25QXXX.h"

#define SPI_IS_BUSY 	(HAL_GPIO_ReadPin(FLASH_CS_GPIO_Port, FLASH_CS_Pin)==GPIO_PIN_RESET)

extern SPI_HandleTypeDef FLASH_SPI_PORT;




/******************************************
 * @brief	enable Flash SPI port
 * 			any command on Flash, any transmission, must start with
 * 			a Chip Select and terminate with a Chip Unselect.
 * 			So testing CS pin let understand if a
 * 			transmission is still running:
 * 			before selecting chip a test over the same CS let
 * 			understand if previous transmission terminated
 ******************************************/
void Flash_Select(void) {
		while (SPI_IS_BUSY) {}
		HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET);
}




/******************************************
 * @brief	disable Flash SPI
 * 			verifying that there is no a running data transfer
 ******************************************/
void Flash_UnSelect(void) {
	// CS pin must be low (selected flash) until previous transmission is completed
#ifdef	EXT_FLASH_SPI_POLLING_MODE
	HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);	//unselect
#endif  // FLASH_SPI_POLLING_MODE
}




void Flash_Receive(uint8_t* data, uint16_t dataSize){
	HAL_SPI_Receive (&FLASH_SPI_PORT , data, dataSize, HAL_MAX_DELAY);
}



/**********************************************************************
 * @BRIEF	engages SPI port tranferring data to Flash
 * 			just using Polling mode (TouchGFX requires this function)
 * @PARAM	data		buffer data to send
 * 			dataSize	number of bytes in "data" to be sent
 *********************************************************************/
void Flash_Polling_Transmit(uint8_t* data, uint16_t dataSize){
	HAL_SPI_Transmit(&FLASH_SPI_PORT , data, dataSize, HAL_MAX_DELAY);
}




/**************************
 * @BRIEF	engages SPI port tranferring data to Flash
 * 			Macro parameter DISPL_DMA_CUTOFF defines if transmission is Poling or DMA
 * 			you need to set this macro even using TouchGFX (having its own configuration parameter:
 * 			set DISPL_DMA_CUTOFF and CubeMX parameter to the same value)
 * @PARAM	data		buffer data to send
 * 			dataSize	number of bytes in "data" to be sent
 **************************/
void Flash_Transmit(uint8_t* data, uint16_t dataSize){
#ifndef	EXT_FLASH_SPI_POLLING_MODE
	if (dataSize<EXT_FLASH_DMA_CUTOFF) {
#endif //FLASH_SPI_POLLING_MODE
		HAL_SPI_Transmit(&FLASH_SPI_PORT , data, dataSize, HAL_MAX_DELAY);
#ifndef	EXT_FLASH_SPI_POLLING_MODE
	} else {
		HAL_SPI_Transmit_DMA(&EXT_FLASH_SPI_PORT , data, dataSize);
	}
#endif  //FLASH_SPI_POLLING_MODE
}





/**************************
 * @BRIEF	keeps looping inside this function until "BUSY" bit in SR1 register
 * 			becomes 0, meaning that the runnin data operation (writing or erasing)
 * 			on the chip, ended
 **************************/
void Flash_WaitForWritingComplete(){
uint8_t buffer[1];
	Flash_Select();
	buffer[0] = W25_R_SR1;
	Flash_Transmit(buffer, 1);
	do {
		Flash_Receive(buffer, 1);  //SR1 is repeteadly sent until Flash is selected
	} while (buffer[0] & SR1_BIT_BUSY);
	Flash_UnSelect();
}





/**************************
 * @BRIEF	reads from Flash Eeprom
 * 			using "communication mode" selected by
 * 			command doesn't check for the BUSY flag in SR1
 * 			that must be done before calling this function
 * 			current version of library doesn't need it
 * @PARAM	addr		EEPROM address to start reading
 *  		data		buffer to fill with read data
 * 			dataSize	number of bytes to read
 **************************/
void Flash_Read(uint32_t addr, uint8_t* data, uint32_t dataSize){
uint16_t data_to_transfer;
uint8_t buffer[5];

	buffer[0] = FLASH_READ_COMMAND;
	buffer[1] = (addr >> 16) & 0xFF;
	buffer[2] = (addr >> 8) & 0xFF;
	buffer[3] = addr & 0xFF;
	buffer[4] = W25_DUMMY;
	Flash_Select();
	Flash_Transmit(buffer, (FLASH_READ_COMMAND == W25_READ ? 4 : 5));  // "normal/slow" read command doesn't need sending dummy byte

	// dataSize is 32 bit, spi_receive handles 16bit transfers, so I have to loop...
	while (dataSize) {
		data_to_transfer = ((dataSize>0xFFFF) ? 0xFFFF : (uint16_t)dataSize);
		Flash_Receive(data, data_to_transfer);
		data+=data_to_transfer;
		dataSize-=data_to_transfer;
	}
	Flash_UnSelect();
}








/***********************************************************************
 * @BRIEF	it writes into a single FLASH page
 * 			function doesn't check for the BUSY flag in SR1
 * 			function doesn't check for the EEPROM writing enabled
 * 			function doesn't wait for the writing complete
 * 			function doesn't check for the EEPROM page boundary override
 * @PARAM	addr		EEPROM address to start writing
 *  		data		buffer containing data to write into EEPROM
 * 			dataSize	number of bytes to write
 ***********************************************************************/
void Flash_SimpleWriteAPage(uint32_t addr, uint8_t* data, uint16_t dataSize){
uint8_t buffer[4];
	buffer[0] = W25_PAGE_P;
	buffer[1] = (addr >> 16) & 0xFF;
	buffer[2] = (addr >> 8) & 0xFF;
	buffer[3] = addr & 0xFF;
	Flash_Select();
	Flash_Transmit(buffer, 4);
	Flash_Transmit(data, dataSize);
	Flash_UnSelect();
}






/***********************************************************************
 * @BRIEF	function writing into EEPROM
 * 			Handling "write enable" commands
 * 			It splits (if needed) received data into the single pages,
 * 			lounching writing sessions for each page
 * 			and waiting the writing complete each time
 * @PARAM	addr		EEPROM address to start writing
 *  		data		buffer containing data to write into EEPROM
 * 			dataSize	number of bytes to write
 ***********************************************************************/
void Flash_Write(uint32_t addr, uint8_t* data, uint32_t dataSize){
uint8_t buffer[4];
uint16_t quota;
uint32_t inpage_addr;

	if (dataSize==0)
		return;

	// quota is the data size trasferred until now
	quota=0;

	// define the starting write position inside the first Flash page to write...
	inpage_addr=addr & (EXT_FLASH_PAGE_SIZE-1);

	// ... so I can detect if more than 1 Flash page has still to be written
	while ((dataSize-quota+inpage_addr)>EXT_FLASH_PAGE_SIZE){
	//loop here inside, until more than 1 Flash page...

		Flash_Select();
		buffer[0] = W25_W_ENABLE;
		Flash_Transmit(buffer, 1);
		Flash_UnSelect();
		Flash_SimpleWriteAPage(addr+quota,data+quota,(EXT_FLASH_PAGE_SIZE-inpage_addr));
		quota+=(EXT_FLASH_PAGE_SIZE-inpage_addr);
		// having aligned data to page border on the first writing
		// next writings start from 0 position inside a page
		inpage_addr=0;
		Flash_WaitForWritingComplete();
	}
	// now just the final Flash page...
	if (dataSize-quota) {
		Flash_Select();
		buffer[0] = W25_W_ENABLE;
		Flash_Transmit(buffer, 1);
		Flash_UnSelect();
		Flash_SimpleWriteAPage(addr+quota,data+quota,dataSize-quota);
		Flash_WaitForWritingComplete();
	}
}





/**********************************
 * @BRIEF	Erase to 0XFF all bytes in a 4k block
 * 			4k block bounary is 0x1000, that means:
 * 			0x1000, 0x2000, 0x3000, ...
 * 			waiting the writing complete in each page
 * @PARAM	addr	starting erase address
 * 					(it must be a 4k sector boundary)
 *********************************/
void Flash_SErase4k(uint32_t addr){
uint8_t buffer[4];
	Flash_Select();
	buffer[0] = W25_W_ENABLE;
	Flash_Transmit(buffer, 1);
	Flash_UnSelect();

	buffer[0] = W25_S_ERASE4K;
	buffer[1] = (addr >> 16) & 0xFF;
	buffer[2] = (addr >> 8) & 0xFF;
	buffer[3] = addr & 0xFF;
	Flash_Select();
	Flash_Transmit(buffer, 4);
	Flash_UnSelect();
	Flash_WaitForWritingComplete();
}




/**********************************
 * @BRIEF	Erase to 0XFF all bytes in a 32k block
 * 			32k block bounary is 0x08000, that means:
 * 			0x008000, 0x010000, 0x018000, ...
 * 			waiting the writing complete in each page
 * @PARAM	addr	starting erase address
 * 					(it must be a 32k block boundary)
 *********************************/
void Flash_BErase32k(uint32_t addr){
uint8_t buffer[4];
	Flash_Select();
	buffer[0] = W25_W_ENABLE;
	Flash_Transmit(buffer, 1);
	Flash_UnSelect();

	buffer[0] = W25_B_ERASE32K;
	buffer[1] = (addr >> 16) & 0xFF;
	buffer[2] = (addr >> 8) & 0xFF;
	buffer[3] = addr & 0xFF;
	Flash_Select();
	Flash_Transmit(buffer, 4);
	Flash_UnSelect();
	Flash_WaitForWritingComplete();
}





/**********************************
 * @BRIEF	Erase to 0XFF all bytes in a 64k block
 * 			64k block bounary is 0x08000, that means:
 * 			0x010000, 0x020000, 0x030000, ...
 * 			waiting the writing complete in each page
 * @PARAM	addr	starting erase address
 * 					(it must be a 64k block boundary)
 *********************************/
void Flash_BErase64k(uint32_t addr){
uint8_t buffer[4];
	Flash_Select();
	buffer[0] = W25_W_ENABLE;
	Flash_Transmit(buffer, 1);
	Flash_UnSelect();

	buffer[0] = W25_B_ERASE64K;
	buffer[1] = (addr >> 16) & 0xFF;
	buffer[2] = (addr >> 8) & 0xFF;
	buffer[3] = addr & 0xFF;
	Flash_Select();
	Flash_Transmit(buffer, 4);
	Flash_UnSelect();
	Flash_WaitForWritingComplete();
}




/**********************************
 * @BRIEF	Full chip erase to 0XFF
 * 			Chip Erase may need up to 100s
 * 			(typ. 20s)
 * 			waiting the writing complete in each page
 *********************************/
void Flash_ChipErase(){
uint8_t buffer[4];
	Flash_Select();
	buffer[0] = W25_W_ENABLE;
	Flash_Transmit(buffer, 1);
	Flash_UnSelect();

	buffer[0] = W25_CH_ERASE;
	Flash_Select();
	Flash_Transmit(buffer, 1);
	Flash_UnSelect();
	Flash_WaitForWritingComplete();
}





/**********************************
 * @BRIEF	Initiates a powerdown
 * 			after a powerDown only accepted a porweUp command
 * 			opwerDown operation is 3us long
 *********************************/
void Flash_PowerDown(){
uint8_t buffer[4];

	buffer[0] = W25_POWERDOWN;
	Flash_Select();
	Flash_Transmit(buffer, 1);
	Flash_UnSelect();
}







/**********************************
 * @BRIEF	Release from powerdown (3 us to restart) or read device ID
 *********************************/
void Flash_PowerUp(){
uint8_t buffer[4];

	buffer[0] = W25_POWERUP_ID;
	Flash_Select();
	Flash_Transmit(buffer, 1);
	Flash_UnSelect();
	HAL_Delay(1);
}




/**********************************
 * @BRIEF	read device id from chip
 * @RETURN	device id
 *********************************/
uint8_t Flash_ReadDevID(){
uint8_t buffer[4];
uint8_t data;

	buffer[0] = W25_POWERUP_ID;
	buffer[1] = W25_DUMMY;
	buffer[2] = W25_DUMMY;
	buffer[3] = W25_DUMMY;
	Flash_Select();
	Flash_Transmit(buffer, 4);
	Flash_Receive(&data, 1);
	Flash_UnSelect();
	return data;
}





uint16_t Flash_ReadManufactutrerAndDevID() {
uint8_t buffer[4];
uint16_t data;

	buffer[0] = W25_POWERUP_ID;
	buffer[1] = W25_DUMMY;
	buffer[2] = W25_DUMMY;
	buffer[3] = W25_DUMMY;
	Flash_Select();
	Flash_Transmit(buffer, 4);
	Flash_Receive((uint8_t*)&data, 2);
	Flash_UnSelect();
	return data;
}




/******************************************************************
 * @RETURN	32bit value divided in 4 bytes:
 * 			(1)MSB	dummy
 * 			(2)		Jedec Manufacturer ID
 * 			(3)		Memory Type
 * 			(4)		Capacity
 ******************************************************************
 * Memory Capacity code:
 * 			10H ->	 5Mb		11H ->  10Mb		12H ->  20Mb
 * 			13H ->  40Mb		14H ->  80Mb		15H ->  16Mb
 * 			16H ->  32Mb		17H ->  64Mb		18H -> 128Mb
 * 			19H -> 256Mb		20H -> 512Mb		21H ->   1Gb
 ******************************************************************/
uint32_t Flash_ReadJedecID() {
uint8_t buffer[4];
uint8_t data[3];
uint32_t result;

	buffer[0] = W25_JEDEC_ID;
	Flash_Select();
	Flash_Transmit(buffer, 1);
	Flash_Receive(data, 3);
	Flash_UnSelect();
	result=((data[0]<<16) | (data[1] <<8) | data[2]);
	return result;
}




/*********************************
 * @RETURN	256byte SFDP register content:
 *********************************/
void Flash_ReadSFDP(uint8_t* data) {
uint8_t buffer[5];
	buffer[0] = W25_R_SFPD_REG;
	for (uint8_t k=1;k<5;k++)
		buffer[k]=0;
	Flash_Select();
	Flash_Transmit(buffer, 5);
	Flash_Receive(data, 256);
	Flash_UnSelect();
}





/*********************************
 * @BRIEF	testing chip alive and kicking
 * 			reading SFDP record, it must return
 * 			a string beginning with "SFDP"
 * @RETURN	1 	test passed
 * 			0	no
 *********************************/
uint8_t Flash_TestAvailability() {
uint8_t data[256];
uint8_t test=1;

	for (uint8_t k=0;k!=254;k++)
		  data[k]=0xFF;
	Flash_ReadSFDP(data);
	if (data[0]!='S')
		test=0;
	if (data[1]!='F')
		test=0;
	if (data[2]!='D')
		test=0;
	if (data[3]!='P')
		test=0;
	return test;
}




/******************************************************************
 * @BRIEF	reading manufacutrer and device ID
 * 			checking if connected device is a Winbond Flash
 ******************************************************************/
uint8_t Flash_Init(){
uint32_t JedecID;
	HAL_Delay(6);	// supposing init is called on system startup: 5 ms (tPUW) required after power-up to be fully available
	Flash_Reset();
	if (!Flash_TestAvailability())
		return 0;
	JedecID=Flash_ReadJedecID() ;	//select the memSize byte
	if (((JedecID >> 16) & 0XFF) != 0xEF)  // if ManufacturerID is not Winbond (0xEF)
		return 0;
	return 1;  //return memSize as per table in Flash_ReadJedecID() definition
}





void Flash_Reset(){
uint8_t command;
	command = W25_RESET_EN;
	Flash_Select();
	Flash_Transmit(&command, 1);
	Flash_UnSelect();
	command = W25_RESET;
	Flash_Select();
	Flash_Transmit(&command, 1);
	Flash_UnSelect();
	HAL_Delay(1);	// 30us needed by resetting
}







void DataReader_WaitForReceiveDone(){
// nothing to do, being reading always in polling mode
	return;
}

void DataReader_ReadData(uint32_t address24, uint8_t* buffer, uint32_t length){
	Flash_Read(address24, buffer, length);
}


void DataReader_StartDMAReadData(uint32_t address24, uint8_t* buffer, uint32_t length){
//currently using polling mode even if requested DMA
	Flash_Read(address24, buffer, length);
}







