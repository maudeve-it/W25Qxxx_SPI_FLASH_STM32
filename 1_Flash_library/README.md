**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_
_**<br>Below the English text you'll find the Italian version</i>**_
<br>
<br>
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
<br><i><b>
<br>

[Back to the home page](../.)

</b></i><br>

<br>

## GitHub Folders

This guide is divided in 4 chapters following the above list.<br><br>

- [handling an external W25Q flash with this library](./1_Flash_library)
- [creating and using an External Loader for the SPI flash](./2_ExternalLoader)
- [mapping an external SPI flash on CubeIDE projects](./3_CubeIDE_mapping)
- [using an external SPI flash in TouchGFX projects](./4_TouchGFX_mapping)

<br>


<br>
<br>

---
<br>
<br>
<br>




# Gestire un chip SPI Flash W25Q di Winbond con questa libreria
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
<br><i><b>
<br>

[Torna alla home page](../.)

</b></i><br>

<br>
