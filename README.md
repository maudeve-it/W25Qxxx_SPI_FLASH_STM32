_**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_
_**<br>Below the English text you'll find the Italian version</i>**_
<br>
<br>
<br>

# Winbond W25QXXXX SPI FLASH memories with STM32: <br>
## including support functions for External Loaders<br>
## and for the flash integration on TouchGFX projects<br>
<br><br>
In this GitHub page, you'll find a library for STM32 (HAL) handling <b>Winbond SPI Flash memories (W25Qxxxx)</b>.<br>
Library includes functions needed to generate <b>External Loaders</b> for STM32CubeProgrammer and STM32CubeIDE.<br>
Inside library are also functions needed handling an external flash memory in <b>TouchGFX</b> projects, storing font and images, using a direct transfer flash->display (without needing a cache in RAM).<br>
<br>Current version of library handles SPI communication via:
-	<b>standard SPI</b>: W25Q handle QuadSPI. This library communicate using Standard SPI<br>
-	<b>polling mode</b>: no "interrupt mode" o "DMA mode"<br>
See youtube video to know advantages of this approach.<br><br><br><br>

### video Support
Here you can find video documentation about these topics

|||
|---|---|
|z|z|
|||


### References
sofware, this page and above videos, were developed upon this documentation:

|||
|---|---|
|STM Mooc - External QSPI loader how to|https://www.st.com/content/st_com/en/support/learning/stm32-education/stm32-moocs/external_QSPI_loader.html|
|STM repository of external flash loaders|https://github.com/STMicroelectronics/stm32-external-loader|
|STM32CubeProgrammer documentation|https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf|
|STM32 Graphics: external QSPI flash in TouchGFX|https://youtu.be/RMgVo_uCTbw|
|TouchGFX: Using Serial Flash for images and fonts|https://support.touchgfx.com/docs/development/scenarios/using-serial-flash|



# 1) Handling the W25QXXXX Winbond SPI Flash chip library
Here youl find documentation about haw to handle a flash memory chip connected to a uC SPI port
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
FLASH_SCK<br>
FLASH_MISO<br>
FLASH_MOSI<br>
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

# Creating an EXTERNAL LOADER for STM32CubeProgrammer and STM32CubeIDE
External Loader is a plug-in for STM32CubeProgrammer allowing to read/write an external memory through an STM32 uC.<br>
Through the library shown above it is possible to create an External Loader for an STM32 project having a Winbond external SPI Flash chip .<br>
You can use the same external loader file in STM32CubeIDE to program external Flash memory directly while creating a project: CubeIDE uses the CubeProgrammer modules to program uC internal and external flash memory.  

## "How to" create an External Loader for a specific project:
<ul>
Supposing you already defined the project configuration having an external flash memory (having defined the SPI port and CS pin and other details needed to communicate with Flash memory)<br><br>
<li><b>Create a new project in CubeIDE</b>.<br>
Give the project a name with this format:<br> 
"external flash used"_"uC or board name"_"other info, if any, - e.g. SPI port, CS pin, etc."<br>
(character "_" divides the three fields and must non be used if not for this porpose)<br>
Here some examples for a valid project name:
<ul>
W25Q80_STM32F411_SPI1<br>
W25Q80_BLACKPILL-F411 (third field is optional and here it is not used)<br>
W25Q64_NUCLEO32-L432_SPI1-PA4CS<br>
etc.<br>
</ul>
<li><b>in CubeMX</b>:
<ul>
<li> setup the <b>SPI port</b> and the <b>CS pin</b> for your flash memory. (see above details about CubeMX configuration)<br>
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

# "How to" add External Loader to STM32CubeProgrammer
<ul>
<li>
Go to the STM32CubeProgrammer program folder<br> 
(for instance: right-click the program icon and choose "opern file location")
<li>
once in the STM32CubeProgrammer program folder go into "ExternalLoader" subfolder
<li>
here put the External Loader created (.stldr file)<br><br>
Opening STM32CubeProgrammer program you can select the new External Loader to access the external flash memory.
</ul>

# add External Loader to STM32CubeIDE
<br>STILL UNDER DEVELOPEMENT<br><br>

# "How to" setup a TouchGFX project mapping an external flash memory
<br>STILL UNDER DEVELOPEMENT<br><br>

---
> The software, schemes and PCB designs in this set of repositories are provided just for 
> illustrative purposes, sharing the personal experience on this project. 
> The software and design artifacts are provided as-is without any mantainence and without
> warranty of any kind. There is no guarantee of fitness for any particular application, 
> and no guarantee of completeness and correctness. 
> By downloading and using these materials the user accepts all risks associated with the
> construction and use of the circuits and devices described in these design files.

---

## NOTES
<br>STILL UNDER DEVELOPEMENT<br><br>

---

<br>
<br>

# Memorie SPI Flash Winbond W25QXXXX con STM32: <br>
## incluse le funzioni per creare External Loader,<br>
## e per integrare la flash in progetti TouchGFX<br>
<br><br>
In questa pagina GitHub trovi una libreria di funzioni per STM32 (HAL) per la gestione di <b>memorie SPI Flash Winbond (W25Qxxxx)</b>.<br>
La libreria include anche le funzioni richieste per generare <b>External Loader</b> per STM32CubeProgrammer o per STM32CubeIDE.<br>
Nella libreria sono presenti anche le funzioni richeste per integrare una memoria Flash esterna in progetti <b>TouchGFX</b> per memorizzare font ed immagini con trasferimento diretto flash->display (non è richiesta cache in RAM).<br>
<br>La versione corrente della libreria gestisce la comunicazione via:
-	<b>standard SPI</b>: i chip W25Q possono comunicare in QuadSPI, questa versione della libreria gestisce Standard SPI<br>
-	<b>polling mode</b>: non è gestita la comunicazione "interrupt mode" o "DMA mode"<br>
Vedi questo video youtube per conoscere i vantaggi di questo approccio.<br><br><br><br>


### Supporto video
Qui puoi trovare video relativi ai temi trattati in questa pagina
|||
|---|---|
|z|z|
|||


### Referimenti
Il software, questa pagina ed i video sopra sono stati sviluppati sulla base di queste informazioni:

|||
|---|---|
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
Ipotizzando che hai gia' creato la configurazione del progetto di memoria esterna (hai già definito la porta SPI ed il pin CS da usare per la comunicazione con la memoria Flash...)<br><br>
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
<li> configura una porta <b>SPI</b> ed il pin <b>CS</b> per la memoria flash (vedi spora il dettaglio per la configurazione CubeMX)<br>
<i><b>Attenzione</b><br>
per External Loader e' consigliabile configurare una velocià inferiore a 2Mbit/s</i><br>
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

# add External Loader to STM32CubeProgrammer
<ul>
<li>
andare nel folder del programma STM32CubeProgrammer<br> 
(ad esempio right-click the program icon and choose "opern file location")
<li>
dal program folder scegliere la cartella "ExternalLoader"
<li>
copiare qui il file .stldr creato<br><br>
Aprendo STM32CubeProgrammer si puo' selezionare il nuovo External Loader per accedere alla memoria Flash esterna
</ul>






# add External Loader to STM32CubeIDE
<br>ANCORA IN SVILUPPO<br><br>




# "How to" come configurare un progetto TouchGFX con una memoria flash mappata
<br>ANCORA IN SVILUPPO<br><br>



---
> Il software e gli schemi di progetto come i layout PCB in questa serie di repository 
> sono messe a disposizione con puro intento illustrativo e di condivisione dell'esperienza fatta
> Il software and gli elementi del progetto sono messi a disposizione "allo stato in cui sono"
> senza impegno di manutenzione e senza garanzie di alcun tipo. Piu' esplicitamente, non c'e' garanzia di 
> adeguatezza a soddisfare specifiche esigenze, ne di completezza o correttezza di alcuna parte.
> Scaricando ed utilizzando questo materiale l'utilizzatore accetta il rischio associato alla
> realizzazione ed all'utilizzo del circuito e dei componenti descritti in questi file.

---

## NOTE
<br>ANCORA IN SVILUPPO<br><br>

