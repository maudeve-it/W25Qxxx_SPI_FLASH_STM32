**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_
_**<br>Below the English text you'll find the Italian version</i>**_
<br>
<br>
<br>

# A W25QXXX SPI FLASH memory library for STM32: <br>
## including support functions for External Loaders developing<br>
## and for the flash memory integration on TouchGFX projects<br>
<br><br>
In this GitHub page, you'll find a library for STM32 (HAL) handling <b>Winbond SPI Flash memories (W25Qxxx)</b>.<br>
Library includes functions you need to create <b>External Loaders</b> for STM32CubeProgrammer and STM32CubeIDE.<br>
Inside library you'll find also functions, that <b>TouchGFX</b> needs to handle an external flash memory, reading font and images via a direct transfer flash->display (without needing a cache in RAM).<br>
So, you can use this software for 4 distinct purposes:
<ul>
<li>handling an external W25Q flash directly reading and writing over it<br></li>
<li>create an External Loader to program flash memory via CubeProgrammer<br></li>
<li>add the created external loader to a CubeIde project in order to directly flash the external chip while creating projects (as same as the uC internal flash memory)<br></li>
<li>add an external flash to a TouchGFX project. TouchGFX provides tools making an external flash, handled via an external loader, absolutely transparent to the project.<br> </li>
</ul>
<br>
The following documentation is divided in 4 chapters following the above list.<br><br>
Current version of library handles SPI communication via:<br>
<ul>
<li><b>standard SPI</b>: W25Q handles QuadSPI but this library communicate using Standard SPI<br></li>
<li><b>polling mode</b>: no "interrupt mode" nor "DMA mode"<br></li>
</ul>
See youtube videos to know advantages of this approach.<br><br>

### Helping videos
Here you can find video documentation about these topics:

|||
|---|---|
|Part one: "how to" use library, "how to" develop an EL, "how to" install an EL into CubeProgrammer|https://youtu.be/KlG2doCkREM|
|Part two: "how to" use the SPI flash in TouchGFX projects, "how to" install an EL into CubeIDE to progam the flash memory in a TouchGFX project||
|Part three: "how to" handle an external SPI flash memory in a CubeIDE project||

<br>

### Sources
The  sofware you find on this page, the page content and above videos, were developed upon this documentation:

|||
|---|---|
|Winbond W25Qxxx web page|https://www.winbond.com/hq/product/code-storage-flash-memory/serial-nor-flash|
|Jedec SFDP standard (requires registration)|https://www.jedec.org/document_search/field_doc_type/148?search_api_views_fulltext=JESD216|
|STM Mooc - External QSPI loader how to|https://www.st.com/content/st_com/en/support/learning/stm32-education/stm32-moocs/external_QSPI_loader.html|
|STM repository of external flash loaders|https://github.com/STMicroelectronics/stm32-external-loader|
|STM32CubeProgrammer documentation|https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf|
|STM32 Graphics: external QSPI flash in TouchGFX|https://youtu.be/RMgVo_uCTbw|
|TouchGFX: Using Serial Flash for images and fonts|https://support.touchgfx.com/docs/development/scenarios/using-serial-flash|

<br>


# 1) Using the W25QXXXX Winbond SPI Flash chip library
Here you'll find documentation about handling a flash memory chip connected to a uC SPI port
<ul>
<li><b>(1)	in CubeMX</b>:<br>
creating your STM32 project assign an SPI port to the communication with the Flash memory.<br>
SPI must be set this way:<br><br>

|Mode|value|
|---|---|
|mode|Full-Duplex Master|
|NSS|Disable|


|Parameter|value|
|---|---|
|Frame format|Motorola|
|Data size|8 bit|
|First bit|MSB first|	
|CPOL|low|
|CPHA|1 Edge|
|CRC calculation|disabled|
|NSS type|Output Sw|

SPI pins must have these names:
<ul>
<b>
FLASH_SCK<br>
FLASH_MISO<br>
FLASH_MOSI<br>
</b>
</ul>

<br>
Setup a pin as GPIO_Output:</b><br>

|pinname to assign|output level|mode|pull-up/down|
|---|---|---|---|
|FLASH_CS|high|Output push pull|No pull-up/down|

Pin speed affects SPI port: rise (step by step from LOW to VERY HIGH) pins speed if you see uC cannot handle the defined communication speed (more information on your uC datasheet).<br>
</li>

<br>
<li>
<b>(2)	in CubeIDE</b>:<br>
after saving CubeMX and after C code generation:<br>
<ul>
copy into the "include" folder (core\inc) <i>z_flash_W25QXXX.h</i> file<br>
copy into the "source" folder (core\src) <i>z_flash_W25QXXX.c</i> file <br>
</ul>
</li>
<br>
<li>
<b>(3)	in <i>main.h</i></b>:<br>
open file <i>main.h</i>
and edit <i>/* USER CODE BEGIN Includes */</i> segment, this way:
<br>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "z_flash_W25QXXX.h"
/* USER CODE END Includes */
...
```
<br>
</li>
<li>
<b>(4)	in <i>z_flash_W25QXXX.h</i></b>:<br>
edit file <i>z_flash_W25QXXX.h</i> this way:<br>
<ul>
<li>
	into segment <b>STEP1</b>:<br>
		register SPI used, updating the two lines (hspi1/SPI1, hspi2/SPI2, ...)<br>
<li>
	into segment <b>STEP2</b>:<br>
        no changes: currently available only "Fast Mode"<br>
<li>
    into segment <b>STEP3</b>:<br>
        no changes: currently available only "Polling Mode"<br>
<li>
    into segment <b>STEP4</b>:<br>
        update all parameters with information about memory chip to handle.<br>
        Currently file shows, inside comments, configuration parameters for:<br>
<ul>
            W25Q80DV/DL<br>
            W25Q64JV<br>
            W25Q128JV<br>
</ul>
        if you are using a chip of these, you just need to copy the related commented parameters to the uncommented area <b>STEP4</b><br>
		if you are using a different memory chip, just use this data as example of what is needed for a correct library setup.<br>
<br>
</ul>
</li>
</ul>
Having done what above shown, you can use all functions of the library handling flash.<br>
Each function has its own description and help, inside <b>z_flash_W25QXXX.c</b> file<br>
<br>
<br>

# 2) Creating an EXTERNAL LOADER for STM32CubeProgrammer and STM32CubeIDE
External Loader is a plug-in for STM32CubeProgrammer allowing to read/write an external memory through an STM32 uC.<br>
Through the library shown above it is possible to create an External Loader for an STM32 project having a Winbond external SPI Flash chip .<br>
Next, you will see how you can use the same external loader program in STM32CubeIDE to program external Flash memory directly while creating a project: CubeIDE uses the CubeProgrammer modules to program uC internal and external flash memory.  

## "How to" create an External Loader for a specific project:
<ul>
Supposing you already defined the project configuration having an external flash memory (e.g. having defined the SPI port and CS pin and other details needed to communicate with Flash memory...)<br><br>
<li><b>Create a new project in CubeIDE</b>.<br>
Give the project a name with this format:<br> 
"external flash used"_"uC or board name"_"other info, if any, - e.g. SPI port, CS pin, etc."<br>
(character "_", dividing the three fields, must non be used elsewhere)<br>
Here some examples for a valid project name:
<ul>
W25Q80_STM32F411_SPI1<br>
W25Q80_BLACKPILL-F411 (third field is optional and here it is not used)<br>
W25Q64_NUCLEO32-L432_SPI1-PA4CS<br>
etc.<br>
</ul>
<li><b>in CubeMX</b>:
<ul>
<li> setup the <b>SPI port</b> and the <b>CS pin</b> for your flash memory. (see above details about SPI port configuration on CubeMX)<br>
<br>
<i><b>Warning:</b><br>
if prototyping with a flash on a breakout board, in the External Loader project I recommend to setup an SPI port speed lower than 2Mbit/s</i><br>
<br>
<li> If on your board, you have available a led connected to a uC pin (GPIO_Output): you can use it in the External Loader. Useful for troubleshooting.<br>
give the uC led pin the name: <b>LED</b>.<br>
<li> in <i>"Project Manager"->"Code Generator"</i>, mark <b><i>"Generate peripheral initialization as a pair of '.c/.h' files per peripheral"</i></b> to have peripheral initialing files separated by <i>main.c</i>
<li> generate "c" code.
</ul>
<li><b>in CubeIDE</b>:
<ul>
<li>
in <i><b>include</b></i> folder, copy files:
<ul>
z_flash_W25QXXX.h<br>
Dev_Inf.h<br>
</ul>
<li>
in <i><b>src</b></i> folder, copy files:
<ul>
z_flash_W25QXXX.c<br>
Dev_Inf.c<br>
Loader_Src.c<br>
</ul>
<li>
in <i><b>root</b></i> folder, copy files:
<ul>
EL_linker.ld<br>
Post-Build command.txt<br>
</ul>
<li>
Setup <i>"<b>z_flash_W25QXXX.h</b>"</i>
<ul>
registering flash chip characteristics (see above the setup of <i>"z_flash_W25QXXX.h"</i> Step 1 to 4)
</ul>
<li>
Setup <i><b>Loader_Src.c</b></i>:
<ul>
follow inside file: Step1, Step2, Step3
</ul>
<li>
Setup <i><b>Dev_Inf.c</b></i>: 
<ul>
update first struct field assigning a name to the External Loader: copy here the project name<br>
update third struct field indicating address where external flash is mapped<br>
leave unchanged other fields.
</ul>
<li>
open file <i>"<b>Post-Build command.txt</b>"</i>
<ul>
copy the text row and paste it into the field in<br>
<i>project->properties->C/C++ Build->settings->Build Steps->Post-Build Steps->Command</i><br>
click "Apply and Close"
</ul>
<li>
edit <i><b>EL_linker.ld</b></i> 
<ul>
<li>
set the memory size as per uC available RAM:<br>
around line 30 you find text:<br>
	
```sh
(EL_linker.ld)
...
RAM (xrw)      : ORIGIN = 0x20000004, LENGTH = xxxK
...
```
<br>
change value after "LENGTH =" indicating the uC RAM size
<li>
save changes
<li>
in <i><b>project->properties->C/C++ Build->settings->Tool Setting->MCU GCC Linker->General->linker script</b></i>:
<ul>
1	change the name of the .ld file into "EL_linker.ld". Parameter should become: ${workspace_loc:/${ProjName}/EL_linker.ld}<br>
2	remove flag in <i><b></b>Discard Unused Sections</i>b></i><br>
3	click "Apply and Close"<br>
</ul>
</ul>
</ul>
</ul>
Now "Compile" progetto: If everithing is good <b>you'll find the file <i>project_name</i>.stldr into the project root folder</b><br><br> 
THIS IS THE EXTERNAL LOADER<br><br>

## "How to" add External Loader to STM32CubeProgrammer

<ul>
<li>
Go to the STM32CubeProgrammer program folder<br> 
(right-click the program icon and choose "open file location")
<li>
once in the STM32CubeProgrammer program folder go into "ExternalLoader" subfolder
<li>
copy here the External Loader created (.stldr file)<br><br>
Opening STM32CubeProgrammer program you can select the new External Loader to access the external flash memory.
</ul>

# 3) "How to" setup an STM32CubeIDE project mapping an external flash memory
<br>STILL UNDER DEVELOPEMENT<br><br>

# 4) "How to" setup a TouchGFX project mapping an external flash memory

Setup a TouchGFX project (following https://github.com/maudeve-it/ILI9XXX-XPT2046-STM32)<br>
then:<br>
<li><b>on CubeMX</b>:<br>
<ul>
on TouchGFX package:
<ul>
enable <b>"External Data Reader"</b>	
<ul>
in <b>External data reader: Memory base address</b>
<ul>	
set the memory base address (leave 0x90000000 if no specific needs t ochange it)
</ul>	
in <b>External data reader: Memory size</b>
<ul>	
indicate the size of the external flash memory
</ul>	
other parameters
<ul>	
leave unchanged
</ul>	
</ul>	
</ul>	
generate "c" code.
</ul>	
<li><b>on CubeIDE</b>:<br>
<ul>
in <i><b>include</b></i> folder, copy file:
<ul>
z_flash_W25QXXX.h<br>
</ul>
in <i><b>src</b></i> folder, copy file:
<ul>
z_flash_W25QXXX.c<br>
</ul>
in <i><b>root</b></i> folder, copy files:
<ul>
Program_linker_include.txt<br>
</ul>
Edit file <i>main.h</i>:
<ul>
open it<br>	
modify <i>/* USER CODE BEGIN Includes */</i> segment, adding the flash library include, this way:
<br>
<ul>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
...
#include "z_flash_W25QXXX.h"
...
/* USER CODE END Includes */
...
```
<br>
<ul>
<b>Edit the linker script</b> (<xxxxxxxx_FLASH.ld</b> file):<br>
<ul>
<li>open the linker script file and open also Program_linker_include.txt<br>
<li>from this last file copy the row indicating flash size and address (starting with "SPI_FLASH...")<br> 
<li>in the linker script, in the "<b>Memories definition</b>" area, paste the copied row, obtaining something like this:<br>  

```sh
(xxxxxxFLASH.ld)
...
/* Memories definition */
MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 512K
  SPI_FLASH    (r)    : ORIGIN = 0x90000000,   LENGTH = 1M
}
...
```
<br>
	
<li><b>Do not modify</b> RAM configuration,FLASH one or anyother memory area defined and handled by CubeMX<br>
<li>Change "LENGTH" field <b>of SPI_FLASH</b> indicating the size of flash memory you are using<br>
<li>"ORIGIN" field of SPI_FLASH <b>must be the same value</b> registred in CubeMX TouchGFX configuration<br> 

</ul>
from Program_linker_include.txt file copy rows of the <b>ExtFlashSection</b><br>

```sh
(Program_linker_include.txt)
...
  ExtFlashSection :
  {
	*(ExtFlashSection ExtFlashSection.*)
	*(-gnu-linkonce.r.*)
    . = ALIGN(0x100);
  } >SPI_FLASH
...
```

<ul>
and paste them at the beginning of the SECTIONS area of the linker script. This way:<br>

```sh
(xxxxxxFLASH.ld)
...

/* Sections */
SECTIONS
{
  ExtFlashSection :
  {
	*(ExtFlashSection ExtFlashSection.*)
	*(-gnu-linkonce.r.*)
    . = ALIGN(0x100);
  } >SPI_FLASH
...
```
<ul>
this will allow to move selected images to the external flash memory.

if you want/need to move also fonts to the external memory copy also the  <b>FontFlashSection</b> from Program_linker_include.txt and paste into linker file this way:

```sh
(xxxxxxFLASH.ld)
...

/* Sections */
SECTIONS
{
  ExtFlashSection :
  {
	*(ExtFlashSection ExtFlashSection.*)
	*(-gnu-linkonce.r.*)
    . = ALIGN(0x100);
  } >SPI_FLASH

  FontFlashSection :
  {
    *(FontFlashSection FontFlashSection.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x4);
  } >SPI_FLASH

...
```
<br>

<li><b>on TouchGFX Designer</b>:<br>
<br>
<ul>
From now on, when you are in <b>TouchGFX Designer</b>, you can move single pictures to the external flash assigning them to the <b>ExtFlashSection</b>:<br><br>
<img src="https://github.com/maudeve-it/W25Q-SPI-FLASH-EEPROM-STM32/blob/408667dba8d2794d4badf6d38119551e20747302/designer1.png" width="840" height="429">
<br>
<br>If you want use external flash as the default storage for pictures set it into the <b>Default Image Configuration</b>:<br>
<br>
<img src="https://github.com/maudeve-it/W25Q-SPI-FLASH-EEPROM-STM32/blob/72221b6407f290e69fb63f50fb6f79a94595929c/designer2.png" width="742" height="630">
</ul>
<br>

---
>
> <i><b>WARNING</b></i>
> </b>
> External SPI flash memory is MUCH slower than uC internal flash.<br> 
> Consider to move to the flash what you really need due to the limit of the uC internal flash

---

<br>
<li> add the external loader to CubeIDE
<ul>	
Go to the STM32CubeIDE program folder
(right-click the program icon and choose "open file location")<br>
once in the STM32CubeIDE program folder go to:
<ul>
<i>plugins</i> folder<br>
<i>xxxxxx.externaltools.cubeprogrammer.xxxxx</i> folder<br>
<i>tools</i> folder<br>
<i>bin</i> folder<br>
<i>ExternalLoader</i> folder<br>
</ul>
here copy the external loader you previously made following above instructions<br>
</ul>
<li>configure CubeIDE to use the external loader<br>
<ul>
in CubeIDE go to Project->Properties->Run/Debug Settings<br>
select the settings file and click "Edit"<br>
go to "Debugger"<br>
scroll to "External Loaders" and click "Add"<br>
select, in the external loader list, the external loader to use.
Click "OK" and "Apply" until you close all the "properties" windows open.
	
</ul>	



## NOTES
> The software, schemes and PCB designs in this set of repositories are provided just for 
> illustrative purposes, sharing the personal experience on this project. 
> The software and design artifacts are provided as-is without any mantainence and without
> warranty of any kind. There is no guarantee of fitness for any particular application, 
> and no guarantee of completeness and correctness. 
> By downloading and using these materials the user accepts all risks associated with the
> run of the software and construction and use of the circuits and devices described.<br>
---

---

<br>
<br>

# Una libreria sulle memorie SPI Flash W25QXXXX per STM32: <br>
## incluse le funzioni di supporto per creare External Loader,<br>
## e per integrare la memoria flash in progetti TouchGFX<br>
<br><br>
In questa pagina GitHub trovi una libreria di funzioni per STM32 (HAL) per la gestione di <b>memorie SPI Flash Winbond (W25Qxxxx)</b>.<br>
La libreria include anche le funzioni richieste per generare <b>External Loader</b> per STM32CubeProgrammer o per STM32CubeIDE.<br>
Nella libreria sono presenti anche le funzioni richeste per integrare una memoria Flash esterna in progetti <b>TouchGFX</b> per memorizzare font ed immagini con trasferimento diretto flash->display (non è richiesta cache in RAM).<br>
Puoi utilizzare quindi questo software per 4 scopi distinti:
<ul>
<li>gestire una memoria flash esterna W25Q, leggendo o scrivendo direttamente sopra<br></li>
<li>creare un External Loader per programmare la memoria flash via CubeProgrammer<br></li>
<li>aggiungere l'external loader creato ad un progetto CubeIde allo scopo di programmare direttamente il chip esterno durante la creazione del progetto (come fatto per la flash interna al uC)<br></li>
<li>aggiungere la memoria flash esterna ad un progetto TouchGFX. TouchGFX fornisce strumenti per rendere la memoria flash, gestita tramite un external loader, totalmente trasparente al progetto.<br> </li>
</ul>
<br>
La documentazione di seguito è divisa in 4 parti seguendo lo schema sopra.<br><br>
La versione attuale della libreria gestisce la comunicazione SPI via:<br>
<ul>
<li><b>standard SPI</b>: W25Q gestisce QuadSPI ma questa libreria usa Standard SPI<br></li>
<li><b>polling mode</b>: non viene usato "interrupt mode" nè "DMA mode"<br></li>
</ul>
Vedi i video youtube sotto per conoscere i vantaggi di questo approccio.<br><br><br><br>


### Supporto video
Qui puoi trovare video relativi ai temi trattati in questa pagina

|||
|---|---|
|Prima parte: "how to" - come usare la libreria, come creare un EL, come installare un EL in Cubeprogrammer|[z](https://youtu.be/KlG2doCkREM)|
|Seconda parte: "how to" - come usare la memoria FLash SPI in un progetto TouchGFX, come installare un EL in CubeIDE per programmare la memoria flash in un progetto TouchGFX||
|Terza parte: "how to" gestire una memoria flash SPI in un progetto CubeIDE||


### Referimenti
Il software, questa pagina ed i video sopra sono stati sviluppati sulla base di questa documentazione:

|||
|---|---|
|Winbond W25Qxxx web page|https://www.winbond.com/hq/product/code-storage-flash-memory/serial-nor-flash|
|Jedec SFDP standard (requires registration)|https://www.jedec.org/document_search/field_doc_type/148?search_api_views_fulltext=JESD216|
|STM Mooc - External QSPI loader how to|https://www.st.com/content/st_com/en/support/learning/stm32-education/stm32-moocs/external_QSPI_loader.html|
|STM repository of external flash loaders|https://github.com/STMicroelectronics/stm32-external-loader|
|STM32CubeProgrammer documentation|https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf|
|STM32 Graphics: external QSPI flash in TouchGFX|https://youtu.be/RMgVo_uCTbw|
|TouchGFX: Using Serial Flash for images and fonts|https://support.touchgfx.com/docs/development/scenarios/using-serial-flash|



# Gestire un chip SPI Flash W25Q di Winbond
Qui trovi le informazioni su come gestire una memoria flash connessa alla porta SPI del uC
<ul>
<li><b>(1)	in CubeMX</b>:<br>
durante la creazione del progetto, assegnare una porta SPI per la comunicazione con la memoria Flash.<br>
la porta SPI deve essere configurata così:<br><br>

|Mode|value|
|---|---|
|mode|Full-Duplex Master|
|NSS|Disable|


|Parameter|value|
|---|---|
|Frame format|Motorola|
|Data size|8 bit|
|First bit|MSB first|	
|CPOL|low|
|CPHA|1 Edge|
|CRC calculation|disabled|
|NSS type|Output Sw|

Ai pin della porta SPI assegnare i nomi:
<ul>
FLASH_SCK<br>
FLASH_MISO<br>
FLASH_MOSI<br>
</ul>

<br>
Configura un altro pin come GPIO_Output:</b><br>

|pinname to assign|output level|mode|pull-up/down|
|---|---|---|---|
|FLASH_CS|high|Output push pull|No pull-up/down|

La velocità del pin ha effetti sulla velocità della porta SPI: aumenta (per gradi da LOW to VERY HIGH) la velocità dei pin se vedi che il uC non riesce a gestire la velocità di comunicazione assegnata (maggiori informazioni sul datasheet del tuo uC).<br>

</li>
<br>
<li>
<b>(2)	in CubeIDE</b>:<br>
dopo aver salvato la configurazione CubeMX e generato il codice C:<br>
<ul>
copiare nella cartella "include" (core\inc) il file <i>z_flash_W25QXXX.h</i><br>
copiare nella cartella "source" (core\src) il file <i>z_flash_W25QXXX.c</i><br>
</ul>
</li>
<br>
<li>
<b>(3)	in <i>main.h</i></b>:<br>
aprire il file <i>main.h</i>
e modifica il segmento <i>/* USER CODE BEGIN Includes */</i> in questo modo:
<br>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "z_flash_W25QXXX.h"
/* USER CODE END Includes */
...
```
<br>
</li>
<li>

<b>(4)	in <i>z_flash_W25QXXX.h</i></b>:<br>
aprire il file <i>z_flash_W25QXXX.h</i> e modificare in questo modo:<br>
<ul>
<li>
	nel segmento <b>STEP1</b>:<br>
		indicare la porta SPI utilizzata aggiornando le due voci (hspi1/SPI1, hspi2/SPI2, ...)<br>
<li>
	nel segmento <b>STEP2</b>:<br>
        non modificare: attualmente disponibile solo la modalità "Fast Mode"<br>
<li>
    nel segmento <b>STEP3</b>:<br>
        non modificare: attualmente disponibile solo la modalità "Polling Mode"<br>
<li>
    nel segmento <b>STEP4</b>:<br>
        aggiornare tutti i parametri con le informazioni del chip di memoria utilizzato.<br>
        Attualmente il file contiene nei commenti le configurazioni relative a:<br>
<ul>
            W25Q80DV/DL<br>
            W25Q64JV<br>
            W25Q128JV<br>
</ul>
        se si utilizza uno di questi chip è sufficiente copiare i dati delle righe di configurazione commentate, nell'area di informazione <b>STEP4</b><br>
		se si usano altri chip, usare questi dati come esempio per la configurazione corretta.<br>
<br>
</ul>
</li>
</ul>
Al termine e' possibile utilizzare le varie funzioni della libreria per gestire la memoria Flash<br>
<i>Le funzioni sono autodescritte e commentate nel file <b>z_flash_W25QXXX.c</b></i><br>
<br>
<br>

# creare un EXTERNAL LOADER per STM32CubeProgrammer e STM32CubeIDE
External Loader e' un plug-in per STM32CubeProgrammer per leggere e/o programmare un chip di memoria gestito attraverso da un uC STM32.<br>
Attraverso la libreria di funzioni indicata sopra e' possibile creare un external loader per un progetto STM32 che ha una memoria SPI Flash Winbond esterna .<br>
Lo stesso plugin puo' essere utilizzato in STM32CubeIDE per programmare la memoria Flash direttamente durante la creazione di un progetto: CubeIDE usa i moduli CubeProgrammer per programmare la memoria flash interna od esterna del uC.

## "How to" come creare an External Loader relativo ad un progetto:
<ul>
Ipotizzando che hai gia' creato la configurazione del progetto di memoria esterna (es. hai già definito la porta SPI ed il pin CS da usare per la comunicazione con la memoria Flash...)<br><br>
<li><b>Crea un nuovo progetto in CubeIDE</b>.<br>
Assegna al progetto un nome con questa forma:<br> 
"external flash in uso"_"nome uC o board in uso"_"eventuali altre informazioni - es. Porta SPI, CS pin, ecc."<br>
(il carattere "_" separa i tre campi e non deve essere utilizzato nel nome se non per questa separazione)<br>
Esempi di nomi di progetto protrebbero essere:
<ul>
W25Q80_STM32F411_SPI1<br>
W25Q80_BLACKPILL-F411 (il terzo campo è opzionale e qui non c'e')<br>
W25Q64_NUCLEO32-L432_SPI1-PA4CS<br>
ecc.<br>
</ul>
<li><b>in CubeMX</b>:
<ul>
<li> configura una porta <b>SPI</b> ed il pin <b>CS</b> per la memoria flash (vedi sopra il dettaglio per la configurazione CubeMX)<br>
<i><b>Attenzione:</b><br>
se usato in prototipazione, per External Loader e' consigliabile configurare una velocià inferiore a 2Mbit/s</i><br>
<li> Se hai un led a disposizione sulla scheda, puoi usarlo nell'External Loader (utile nel troubleshooting)<br>
dai al pin del led il nome: <b>LED</b> 
<li> in <i>"Project Manager"->"Code Generator"</i>, spunta <b><i>"Generate peripheral initialization as a pair of '.c/.h' files per peripheral"</i></b> per avere i file di inizializzazione separati da main.c
<li> genera il codice.
</ul>
<li><b>in CubeIDE</b>:
<ul>
<li>
copiare in <i><b>include</b></i> folder
<ul>
z_flash_W25QXXX.h<br>
Dev_Inf.h<br>
</ul>
<li>
copiare in <i><b>src</b></i> folder
<ul>
z_flash_W25QXXX.c<br>
Dev_Inf.c<br>
Loader_Src.c<br>
</ul>
<li>
copiare in <i><b>root</b></i> folder
<ul>
EL_linker.ld<br>
Post-Build command.txt<br>
</ul>
<li>
definire i parametri in <i>"<b>z_flash_W25QXXX.h</b>"</i>
<ul>
definire le caratteristiche della memoria (vedi piu' sopra la configurazione di <i>"z_flash_W25QXXX.h"</i> da Step 1 a 4)
</ul>
<li>
configurare <i><b>Loader_Src.c</b></i>:
<ul>
seguire gli step di configurazione: Step1, Step2, Step3
</ul>
<li>
configurare <i><b>Dev_Inf.c</b></i>: 
<ul>
aggiorna il primo campo della struct assegnando il nome all'External Loader: deve essere "rif alla flash" _ "rif alla board" _ "altre info (es versione)" (copiare il nome del progetto)<br>
aggiorna il terzo campo della struct indicando l'indirizzo su cui e' mappata la flash<br>
non modificare gli altri campi
</ul>
<li>
aprire il file <i>"<b>Post-Build command.txt</b>"</i>
<ul>
copiare il contenuto e incollarlo nel campo in<br>
<i>project->properties->C/C++ Build->settings->Build Steps->Post-Build Steps->Command</i><br>
scegliere "Apply and Close"
</ul>
<li>
modificare <i><b>EL_linker.ld</b></i> 
<ul>
<li>
modificare la dimensione della memoria indicando la RAM disponibile sul uC:<br>
alla riga 30 trovi il testo:<br>
	
```sh
(EL_linker.ld)
...
RAM (xrw)      : ORIGIN = 0x20000004, LENGTH = xxxK
...
```
<br>
modifica il valore dopo "LENGTH =" specificando la dimensione della RAM del uC
<li>
salvare
<li>
in <i><b>project->properties->C/C++ Build->settings->Tool Setting->MCU GCC Linker->General->linker script</b></i>:
<ul>
1	cambiare il nome del file .ld in "EL_linker.ld": dovrebbe essere: ${workspace_loc:/${ProjName}/EL_linker.ld}<br>
2	togliere flag da <i>Discard Unused Sections</i><br>
3	cliccare "Apply and Close"<br>
</ul>
</ul>
</ul>
</ul>
"Compila" il progetto: se tutto e' andato bene <b>trovi il file "nomeprogetto".stldr nella cartella di root</b><br><br> 
Questo e' l'external loader<br><br>

# "How to": come aggiungere un  External Loader a STM32CubeProgrammer
<ul>
<li>
Andare nel folder del programma STM32CubeProgrammer<br> 
(ad esempio click-destro del mouse sull'icona del programma e scegliere "Apri percorso file")
<li>
raggiunta la cartella di STM32CubeProgrammer, scegliere la cartella "ExternalLoader"
<li>
copiare qui il file .stldr creato<br><br>
Aprendo STM32CubeProgrammer si puo' selezionare il nuovo External Loader per accedere alla memoria Flash esterna
</ul>




# "How to" configurare un progetto STM32CubeIDE mappando una memoria flash esterna 
<br>ANCORA IN SVILUPPO<br><br>




# "How to" come configurare un progetto TouchGFX mappando una memoria flash esterna 
Configurare un progetto TouchGFX (segui ad esempio  https://github.com/maudeve-it/ILI9XXX-XPT2046-STM32)<br>
poi:<br>
<li><b>in CubeMX</b>:<br>
<ul>
nel pacchetto TouchGFX:
<ul>
abilitare <b>"External Data Reader"</b>	
<ul>
in <b>External data reader: Memory base address</b>
<ul>	
impostare l'indirizzo dove mappare la memoria (lasciare 0x90000000 se non si anno specifiche esigenze diverse)
</ul>	
in <b>External data reader: Memory size</b>
<ul>	
indicare la dimensione della memoria flash esterna
</ul>	
altri parametri
<ul>	
lasciare come sono
</ul>	
</ul>	
</ul>	
generare il "codice c".
</ul>	
<li><b>su CubeIDE</b>:<br>
<ul>
nella cartella <i><b>include</b></i>, copiare il file:
<ul>
z_flash_W25QXXX.h<br>
</ul>
nella cartella <i><b>src</b></i>, copiare il file:
<ul>
z_flash_W25QXXX.c<br>
</ul>
nella cartella <i><b>root</b></i>, copiare i file:
<ul>
Program_linker_include.txt<br>
</ul>
Modificare il file <i>main.h</i>:
<ul>
aprirlo<br>	
modificare il segmento <i>/* USER CODE BEGIN Includes */</i>, aggiungendo la "include" per la libreria flash:
<br>
<ul>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
...
#include "z_flash_W25QXXX.h"
...
/* USER CODE END Includes */
...
```
<br>
<ul>
<b>Editare lo script per il linker</b> (file <xxxxxxxx_FLASH.ld</b>):<br>
<ul>
<li>aprire lo script per il linker e aprire anche Program_linker_include.txt<br>
<li>da questo ultimo file copiare la riga che indica la misura e l'indirizzo della memoria flash (inizia con "SPI_FLASH...")<br> 
<li>nello script linker, nell'area "<b>Memories definition</b>", incolla la riga copiata, ottenendo una struttura come questa:<br>  

```sh
(xxxxxxFLASH.ld)
...
/* Memories definition */
MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 512K
  SPI_FLASH    (r)    : ORIGIN = 0x90000000,   LENGTH = 1M
}
...
```
<br>
	
<li><b>Non modificare</b> la configurazione RAM, FLASH, o qualunque altra riga si trovi qui: definita e gestita da CubeMX<br>
<li>Modificare il campo "LENGTH" <b>di SPI_FLASH</b> indicando la dimensione della memoria flash in uso<br>
<li>Il campo "ORIGIN" di SPI_FLASH <b>deve avere lo stesso valore</b> registrato nella configurazione TouchGFX in CubeMX<br> 

</ul>
dal file Program_linker_include.txt copia le righe relative a <b>ExtFlashSection</b><br>

```sh
(Program_linker_include.txt)
...
  ExtFlashSection :
  {
	*(ExtFlashSection ExtFlashSection.*)
	*(-gnu-linkonce.r.*)
    . = ALIGN(0x100);
  } >SPI_FLASH
...
```

<ul>
ed incollale all'inizio dell'area SECTIONS dello script linker. In questo modo:<br>

```sh
(xxxxxxFLASH.ld)
...

/* Sections */
SECTIONS
{
  ExtFlashSection :
  {
	*(ExtFlashSection ExtFlashSection.*)
	*(-gnu-linkonce.r.*)
    . = ALIGN(0x100);
  } >SPI_FLASH
...
```
<ul>
questo permette di spostare immagini selezionate verso la memoria flash esterna.

Volendo/dovendo spostrare anche i fontverso la memoria flash esterna, copia anche la sezione <b>FontFlashSection</b> da Program_linker_include.txt ed incollala nello script linker in questo modo:

```sh
(xxxxxxFLASH.ld)
...

/* Sections */
SECTIONS
{
  ExtFlashSection :
  {
	*(ExtFlashSection ExtFlashSection.*)
	*(-gnu-linkonce.r.*)
    . = ALIGN(0x100);
  } >SPI_FLASH

  FontFlashSection :
  {
    *(FontFlashSection FontFlashSection.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x4);
  } >SPI_FLASH

...
```
<br>

<li><b>on TouchGFX Designer</b>:<br>
<br>
<ul>
A questo punto, in <b>TouchGFX Designer</b>, e' possibile spostare singole immagini verso la memoria flash esterna assegnandole a <b>ExtFlashSection</b>:<br><br>
<img src="https://github.com/maudeve-it/W25Q-SPI-FLASH-EEPROM-STM32/blob/main/designer1.png" width="840" height="429">
<br>
<br>Volendo usare la memoria flash esterna come supporto "di default" per archiviare le immagini, impostare il suo valore in <b>Default Image Configuration</b>:<br>
<br>
<img src="https://github.com/maudeve-it/W25Q-SPI-FLASH-EEPROM-STM32/blob/main/designer2.png" width="742" height="630">
<br>
<br>
Se si spostano i font sulla memoria flash esterna <b>OCCORRE SEMPRE</b> impostare i font come "unmapped" in configurazione di <b>TouchGFX Designer</b>:<br>
<br>
<img src="https://github.com/maudeve-it/W25Q-SPI-FLASH-EEPROM-STM32/blob/main/Senzanome.png" width="980" height="526">
<br>
</ul>



---
>
> <i><b>ATTENZIONE</b></i>
> </b>
> La memoria SPI flash esterna is MOLTO più lenta che la flash interna al uC.<br> 
> Tenere in considerazione di spostare sulla flash esterna solo ciò che occorre veramente a causa dei limiti della flash interna al uC.

---

<br>
<li> aggiungere l'external loader a CubeIDE
<ul>	
andare alla cartella del programma to the STM32CubeIDE
(tasto destro del mouse sull'icona del programma e scegli "Apri percorso file")<br>
raggiunta la cartella del programma STM32CubeIDEandare in:
<ul>
cartella <i>plugins</i><br>
cartella <i>xxxxxx.externaltools.cubeprogrammer.xxxxx</i><br>
cartella <i>tools</i><br>
cartella <i>bin</i><br>
cartella <i>ExternalLoader</i><br>
</ul>
copiare qui l'external loader precedentemente creato seguendo following le istruzioni indicate sopra.<br>
</ul>
<li>Configurare CubeIDE per usare l'external loader:<br>
<ul>
in CubeIDE andare in: Project->Properties->Run/Debug Settings<br>
cliccare "Edit"<br>
selezionare "Debugger"<br>
sorrere la pagina fino a "External Loaders" e cliccare "Add"<br>
Selezionare, Nella lista degli external loader, il modulo da usare.
Cliccare "OK" and "Apply" chidendo la finestra "Properties" aperta.
	
</ul>	





---
> Il software e gli schemi di progetto come i layout PCB in questa serie di repository 
> sono messe a disposizione con puro intento illustrativo e di condivisione dell'esperienza fatta
> Il software and gli elementi del progetto sono messi a disposizione "allo stato in cui sono"
> senza impegno di manutenzione e senza garanzie di alcun tipo. Piu' esplicitamente, non c'e' garanzia di 
> adeguatezza a soddisfare specifiche esigenze, ne di completezza o correttezza di alcuna parte.
> Scaricando ed utilizzando questo materiale l'utilizzatore accetta il rischio associato all'esecuzione del programma e alla
> realizzazione ed all'utilizzo del circuito e dei componenti descritti in questo archivio.

---


