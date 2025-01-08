**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_
_**<br>Below the English text you'll find the Italian version</i>**_
<br>
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
if prototyping with a flash on a breadboard, in the External Loader project I recommend to setup an SPI port speed lower than 2Mbit/s</i><br>
<br>
<li> If on your board, you have available a led connected to a uC pin (GPIO_Output): you can use it in the External Loader. Useful for troubleshooting.<br>
give the uC led pin the name: <b>LED</b>.<br>
<li> in <i>"Project Manager"->"Code Generator"</i>, mark <b><i>"Generate peripheral initialization as a pair of '.c/.h' files per peripheral"</i></b> to have peripheral initializing files separated by <i>main.c</i>
<li> generate "c" code.
</ul>
<li><b>in CubeIDE</b>:
<ul>
<li>
in <i><b>Core/inc</b></i> folder, copy files:
<ul>
z_flash_W25QXXX.h<br>
Dev_Inf.h<br>
</ul>
<li>
in <i><b>Core/src</b></i> folder, copy files:
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
2	remove flag in <i><b>Discard Unused Sections</b></i><br>
3	click "Apply and Close"<br>
</ul>
</ul>
</ul>
</ul>
Now "Compile" the project: If everithing is good <b>you'll find the file <i>project_name</i>.stldr into the project root folder</b><br><br> 
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

## "How to" add External Loader to STM32CubeIDE
<br>
see inside page "How to setup a TouchGFX project mapping an external flash memory"
and "How to setup an STM32CubeIDE project mapping an external flash memory"
<br>
<br>
<br>
<br><i><b>
<br>

[Back to the home page](../.)

</b></i><br>

<br>

---

---

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

## "How to": come aggiungere un  External Loader a STM32CubeProgrammer
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


## "How to" add External Loader to STM32CubeIDE
<br>
Vedi la pagina ""How to: come aggiungere un  External Loader a STM32CubeProgrammer"
e ""How to: configurare un progetto STM32CubeIDE mappando una memoria flash esterna"
<br><i><b>
<br>

[Torna alla home page](../.)

</b></i><br>

<br>

