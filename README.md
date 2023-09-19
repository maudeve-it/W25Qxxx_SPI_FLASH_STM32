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

---

<br>

## GitHub Folders

This guide is divided in 4 chapters following the above list.<br><br>

- [handling an external W25Q flash with this library](./1_Flash_library)
- [creating and using an External Loader for the SPI flash](./2_ExternalLoader)
- [mapping an external SPI flash on CubeIDE projects](./3_CubeIDE_mapping)
- [using an external SPI flash in TouchGFX projects](./4_TouchGFX_mapping)

<br>

---

<br>

Current version of library handles SPI communication via:<br>
<ul>
<li><b>standard SPI</b>: W25Q handles QuadSPI but this library communicate using Standard SPI<br></li>
<li><b>polling mode</b>: no "interrupt mode" nor "DMA mode"<br></li>
</ul>
See youtube videos to know advantages of this approach.<br><br><br>

### Helping videos
Here you can find video documentation about these topics:

|||
|---|---|
|Part one: "how to" use library, "how to" develop an EL, "how to" install an EL into CubeProgrammer|https://youtu.be/KlG2doCkREM|
|Part two: "how to" use the SPI flash in TouchGFX projects, "how to" install an EL into CubeIDE|https://youtu.be/PO_2ZE1NQF0|
|Part three: "how to" map an external SPI flash memory in a CubeIDE project||
<br>
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

---

<br>
## Folder GitHub

Questa guida è suddivisa in 4 capitoli seguendo lo schema sopra.<br><br>
- [gestire una memoria flash W25Q attraverso questa libreria](./1_Flash_library)
- [creare and usare an External Loader per le memorie flash SPI](./2_ExternalLoader)
- [mappare una flash SPI esterna sui progetti CubeIDE](./3_CubeIDE_mapping)
- [usare una flash SPI esterna in progetti TouchGFX](./4_TouchGFX_mapping)

<br>

---

<br>

La versione attuale della libreria gestisce la comunicazione SPI via:<br>
<ul>
<li><b>standard SPI</b>: W25Q gestisce QuadSPI ma questa libreria usa Standard SPI<br></li>
<li><b>polling mode</b>: non viene usato "interrupt mode" nè "DMA mode"<br></li>
</ul>
Vedi i video youtube sotto per conoscere i vantaggi di questo approccio.<br><br><br>


### Supporto video
Qui puoi trovare video relativi ai temi trattati in questa pagina

|||
|---|---|
|Prima parte: "how to" - come usare la libreria, come creare un EL, come installare un EL in Cubeprogrammer|[z](https://youtu.be/KlG2doCkREM)|
|Seconda parte: "how to" - come usare la memoria FLash SPI in un progetto TouchGFX, come installare un EL in CubeIDE per programmare la memoria flash in un progetto TouchGFX|https://youtu.be/PO_2ZE1NQF0|
|Terza parte: "how to" mappare una memoria flash SPI in un progetto CubeIDE||
<br><br>

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


<br>


---
> Il software e gli schemi di progetto come i layout PCB in questa serie di repository 
> sono messe a disposizione con puro intento illustrativo e di condivisione dell'esperienza fatta
> Il software and gli elementi del progetto sono messi a disposizione "allo stato in cui sono"
> senza impegno di manutenzione e senza garanzie di alcun tipo. Piu' esplicitamente, non c'e' garanzia di 
> adeguatezza a soddisfare specifiche esigenze, ne di completezza o correttezza di alcuna parte.
> Scaricando ed utilizzando questo materiale l'utilizzatore accetta il rischio associato all'esecuzione del programma e alla
> realizzazione ed all'utilizzo del circuito e dei componenti descritti in questo archivio.

---


