/*********************************************
 * Configuring External loader follow
 * step 1 to 3 hereafter and set the
 * first field in the struct of Dev_Inf.c
 *********************************************/

#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "z_flash_W25QXXX.h"

#define EXT_FLASH_ADDR_MASK 0x0FFFFFFF

/* STEP 1 *************************************
 * remove comment in below #define if you have
 * a led for the External Loader.
 * On CubeMX, led's pin label must be LED
 * ********************************************/
#define IS_LED

/* STEP 2 *************************************
 * change the below #define assigning Pin name
 * and port you used for led,
 * specify also pin level to turn on led
 * ********************************************/
#ifdef IS_LED
#define LED_PIN_ON 	GPIO_PIN_RESET    	//this is the GPIO level turning on led
#endif //IS_LED

/* STEP 3 *************************************
 * change the init function to call as per SPI
 * port used (hint: that's the function
 * available in spi.c, check it)
 * ********************************************/
void LOC_SPI_Init(){
	MX_SPI1_Init();        // !!! this line needs to be aligned to the SPI port used!  Check this function: it is defined in spi.c !!!
}


extern void SystemClock_Config(void);

/**********************************************
 * roughly waints for "Delay" ms before return
 * set uC clock speed. Tested on M4, maybe has
 *  to change using other uC.
 * ********************************************/
void LOC_Delay(uint32_t Delay) {
const uint32_t clock=100; 		// uC MHz
volatile uint32_t delay1;			//
volatile uint32_t multiplier=35;  // that's "converting" Delay value into time spent in the below loop
volatile uint32_t k;
	delay1=Delay;
	for (k=0; (k<(delay1*clock*multiplier)); k++) {};
}



uint32_t HAL_GetTick(void) {
	return 1;
}


void HAL_Delay(uint32_t Delay) {
	LOC_Delay(Delay);
}


HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
	return HAL_OK;
}



void LOC_LedOn(){
#ifdef IS_LED
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LED_PIN_ON);
#endif //IS_LED

}

void LOC_LedOff(){
#ifdef IS_LED
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, !LED_PIN_ON);
#endif //IS_LED
}



int Init (void){

	*(uint32_t*)0xE000EDF0 = 0xA05F0000; //enable interrupts in debug

    SystemInit();

    /* ADAPTATION TO THE DEVICE
     *
     * change VTOR setting for H7 device
     * SCB->VTOR = 0x24000000 | 0x200;
     *
     * change VTOR setting for other devices
     * SCB->VTOR = 0x20000000 | 0x200;
     *
     */

    SCB->VTOR = 0x20000000 | 0x200;

    __set_PRIMASK(0); //enable interrupts

    HAL_Init();
    uint8_t result;

    SystemClock_Config();

    MX_GPIO_Init();
    LOC_SPI_Init();

	LOC_LedOn();
    result = Flash_Init();
	LOC_LedOff();

    __set_PRIMASK(1); //disable interrupts

    return result;

}


		
/**
  * Description :
  * Read data from the device 
  * Inputs    :
  *      Address       : Write location
  *      Size          : Length in bytes  
  *      buffer        : Address where to get the data to write
  * outputs   :
  *      R0             : "1" 			: Operation succeeded
  * 			 		  "0" 			: Operation failure
  * Note: Mandatory for all types except SRAM and PSRAM	
  */
int Read (uint32_t Address, uint32_t Size, uint8_t* buffer){
    __set_PRIMASK(0); //enable interrupts
	Address = Address & EXT_FLASH_ADDR_MASK;
	LOC_LedOn();
	Flash_Read(Address, buffer, Size);
	LOC_LedOff();
    __set_PRIMASK(1); //disable interrupts
	return 1;
} 


	
/**
  * Description :
  * Write data to the device
  * Inputs    :
  *      Address       : Write location
  *      Size          : Length in bytes  
  *      buffer        : Address where to get the data to write
  * outputs   :
  *      R0           : "1" 			: Operation succeeded
  *                     "0" 			: Operation failure
  * Note: Mandatory for all types except SRAM and PSRAM	
  */
int Write (uint32_t Address, uint32_t Size, uint8_t* buffer){
    __set_PRIMASK(0); //enable interrupts
	Address = Address & EXT_FLASH_ADDR_MASK;
	LOC_LedOn();
	Flash_Write(Address, buffer, Size);
	LOC_LedOff();
    __set_PRIMASK(1); //disable interrupts
	return 1;
} 




/**
  * Description :
  * Erase the full chip
  * Inputs    :
  *     None
  * outputs   :
  *     R0             : "1" : Operation succeeded
  * 					 "0" : Operation failure
  * Note: Not Mandatory for SRAM PSRAM and NOR_FLASH
  */
int MassErase (void){
    __set_PRIMASK(0); //enable interrupts
	LOC_LedOn();
	Flash_ChipErase();
	LOC_LedOff();
    __set_PRIMASK(1); //disable interrupts
	return 1;
}



/**
  * Description :
  * Erase a full sector in the device
  * Inputs    :
  *      SectrorAddress	: Start of sector
  *      Size          : Size (in WORD)  
  *      InitVal       : Initial CRC value
  * outputs   :
  *     R0             : "1" : Operation succeeded
  * 			 		 "0" : Operation failure
  * Note: Not Mandatory for SRAM PSRAM and NOR_FLASH
  */
int SectorErase (uint32_t EraseStartAddress ,uint32_t EraseEndAddress) {
	EraseStartAddress = EraseStartAddress & EXT_FLASH_ADDR_MASK;
	EraseEndAddress = EraseEndAddress & EXT_FLASH_ADDR_MASK;

    __set_PRIMASK(0); //enable interrupts
	EraseStartAddress = (EraseStartAddress -  (EraseStartAddress % EXT_FLASH_BLOCK_SIZE));
	while (EraseEndAddress>=EraseStartAddress) {
		LOC_LedOn();
		Flash_BErase64k(EraseStartAddress);
		LOC_LedOff();
		EraseStartAddress += EXT_FLASH_BLOCK_SIZE;
	}
    __set_PRIMASK(1); //disable interrupts
	return 1;
}



/**
  * Description :
  * Calculates checksum value of the memory zone
  * Inputs    :
  *      StartAddress  : Flash start address
  *      Size          : Size (in WORD)  
  *      InitVal       : Initial CRC value
  * outputs   :
  *     R0             : Checksum value
  * Note - Optional for all types of device
  * NOTE - keeping original ST algorithm: not verified and optimized
  */
uint32_t CheckSum(uint32_t StartAddress, uint32_t Size, uint32_t InitVal) {
uint8_t missalignementAddress = StartAddress%4;
uint8_t missalignementSize = Size ;
int cnt;
uint32_t Val;
//uint8_t value;
	
  StartAddress-=StartAddress%4;
  Size += (Size%4==0)?0:4-(Size%4);
  
  for(cnt=0; cnt<Size ; cnt+=4)
  {
	LOC_LedOn();
	Flash_Read(StartAddress + 1,(uint8_t *) &Val, 4);
	LOC_LedOff();

	if(missalignementAddress)
    {
      for (uint8_t k=missalignementAddress; k<=3;k++){
          InitVal += (uint8_t) (Val>>(8*k) & 0xff);
      }
      missalignementAddress=0;
    }
    else if((Size-missalignementSize)%4 && (Size-cnt) <=4)
    {
      for (uint8_t k=(Size-missalignementSize); k<=3;k++){
          InitVal += (uint8_t) (Val>>(8*(k-1)) & 0xff);
      }
      missalignementSize=2 * missalignementSize - Size;
    }
    else
    {
        for (uint8_t k=0; k<=3;k++){
            InitVal += (uint8_t) (Val>>(8*k) & 0xff);
        }
    }
    StartAddress+=4;
  }
  
  return (InitVal);
}


/**
  * Description :
  * Verify flash memory with RAM buffer and calculates checksum value of
  * the programmed memory
  * Inputs    :
  *      FlashAddr     : Flash address
  *      RAMBufferAddr : RAM buffer address
  *      Size          : Size (in WORD)  
  *      InitVal       : Initial CRC value
  * outputs   :
  *     R0             : Operation failed (address of failure)
  *     R1             : Checksum value
  * Note: Optional for all types of device
  * NOTE - keeping original ST algorithm: not verified and optimized
  */

uint64_t Verify (uint32_t MemoryAddr, uint32_t RAMBufferAddr, uint32_t Size, uint32_t missalignement){
#define BUF_SIZE 2
  uint32_t InitVal = 0;
  uint32_t VerifiedData = 0;
//  uint8_t TmpBuffer = 0x00;
	uint64_t checksum;
  Size*=4;
  uint8_t Buffer[BUF_SIZE];
  uint32_t LocAddr = MemoryAddr & EXT_FLASH_ADDR_MASK;
  uint32_t posBuf;
        
  checksum = CheckSum((uint32_t)LocAddr + (missalignement & 0xf), Size - ((missalignement >> 16) & 0xF), InitVal);
  
  while (Size>VerifiedData)
  {
	LOC_LedOn();
	Flash_Read(MemoryAddr+VerifiedData, Buffer, BUF_SIZE);
	LOC_LedOff();

	posBuf=0;
	while ((Size>VerifiedData) && (posBuf<1024)) {
	    if (Buffer[posBuf] != *((uint8_t*)RAMBufferAddr+VerifiedData))
	      return ((checksum<<32) + MemoryAddr+VerifiedData);
	    posBuf++;
	    VerifiedData++;
	}
  }
       
  return (checksum<<32);
}
