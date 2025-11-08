
# Innlevering for Arbeidskrav 5

### Krav for godkjent.
- Bredde-først søk (BFS) fungerer og gir rett resultat for ø5g1 - ø5g7.
- Bredde-først søk kan kjøres med en hvilken som helst node som startsnode.
- Topologisk sortering gir rett resultat på ø5g5 og ø5g7.

### Kompilering
``` bash
gcc bfs.c -o bfs.bin eller bfs.exe
gcc topo.c -o topo.bin eller topo.exe
```

### Kjøring med argumenter
``` bash
./bfs.bin < <filnavn.txt> <startnode>
./topo.bin < <filnavn.txt>
```

### Info
for å få resultat der print-mengden er over terminalens buffer-størrelse:
`./bfs.bin < <filnavn.txt> <startnode> > resultat.txt`