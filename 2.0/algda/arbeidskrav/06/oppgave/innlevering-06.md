# Innlevering 06

### Kompilering
``` bash
gcc compress.c -o bin/compress.bin
gcc decompress.c -o bin/decompress.bin
gcc hufftree.c -o bin/hufftree.bin (optional)
```

### Generering av .bin filer
``` bash
./bin/compress.bin <inputfil>   #[--mkdir] (optional if you want to create output directory)
./bin/decompress.bin <inputfil> #[--mkdir] (optional if you want to create output directory)
```

### Testfiler
Antar at du har en mappe som heter `tests` som du kjører lokalt i terminalen.
``` bash
./bin/compress.bin <din-mappe>/<testfil>    #[--mkdir] (optional om du vil lage export mappe)
./bin/decompress.bin <din-mappe>/<testfil>  #[--mkdir] (optional om du vil lage deexp  mappe)
```

### Addon
Valgte å bruke en buffermetode for å lese og skrive filer, da dette er mer effektivt enn å lese og skrive byte for byte. Dette kan justeres ved å endre `BUFFER_SIZE` definisjonen i både `compress.c` og `decompress.c` filene.