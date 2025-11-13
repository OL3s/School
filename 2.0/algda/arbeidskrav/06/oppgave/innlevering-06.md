# Innlevering 06

### Kompilering
``` bash
gcc compress.c -o .bin/compress.bin
gcc decompress.c -o .bin/decompress.bin
```

### Generering av .bin filer
``` bash
./.bin/compress.bin <inputfil>   #[--mkdir] (optional om du vil lage export mappe)
./.bin/decompress.bin <inputfil> #[--mkdir] (optional om du vil lage deexp  mappe)
```

### Oppgavekjøring
Antar at du har alle oppgavenefilene som du kjører lokalt i terminalen selv.
``` bash
./.bin/compress.bin <din-mappe>/<oppgavefil> 
./.bin/decompress.bin <din-mappe>/<oppgavefil> 
```

### Kommentarer
Valgte å bare fokusere og optimalisere huffmans algoritme slik at jeg klarer å få den så optimal som mulig over å halvveis kombinere flere tilnærminger for å hindre suboptimalisering og kluss, ved dette har jeg inkludert en buffermetode i huffman for å lese og skrive filer, da dette er mer effektivt enn å lese og skrive byte for byte. Dette kan justeres ved å endre `BUFFER_SIZE` definisjonen i både `compress.c` og `decompress.c` filene. Skal ikke lyve, denne oppgaven var utfordrende som også er grunnen til at jeg valgte å fokusere på en ting og gjøre den så bra som mulig.

Laget også `--mkdir` flagget som lager mapper `export` og `deexp` for henholdsvis komprimerte og dekomprimerte filer, dette er for det første for å holde ting ryddig og for det andre for å unngå overskriving av filer i samme mappe, slik at man kan sammenligne begge filer før og etter komprimering og dekomprimering.

Hvis du mener det er en feil at jeg bare har prøvd å laget en optimalisert huffmans algoritme, gi meg gjerne beskjed, så kan jeg prøve å implementere de andre metodene også neste uke.