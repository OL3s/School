# Øving 3, algoritmer og datastrukturer

***Avansert sortering, forske på quicksort med forbedringer***

## Felles godkjenning

- [x] Kildekode og målresultater er med

**Resultater fra kjøring av programmet:**

``` bash
Statistics quicksort
Size: 1        | book 0.000005 seconds | redo 0.000002 seconds | improved 0.000002 seconds | no duplicates 0.000002 seconds
Size: 10       | book 0.000005 seconds | redo 0.000004 seconds | improved 0.000004 seconds | no duplicates 0.000005 seconds
Size: 100      | book 0.000040 seconds | redo 0.000025 seconds | improved 0.000034 seconds | no duplicates 0.000033 seconds
Size: 1000     | book 0.000457 seconds | redo 0.000312 seconds | improved 0.000334 seconds | no duplicates 0.000507 seconds
Size: 10000    | book 0.009713 seconds | redo 0.006689 seconds | improved 0.001925 seconds | no duplicates 0.002935 seconds
Size: 100000   | book 0.132094 seconds | redo 0.125627 seconds | improved 0.005955 seconds | no duplicates 0.014122 seconds
Size: 1000000  | book 9.687041 seconds | redo 9.656452 seconds | improved 0.068800 seconds | no duplicates 0.220841 seconds
```

**Kildekode er levert sammen med denne innleveringen.**

- [x] Tester i koden
    - [x] Avsløring av feil sortering
    - [x] Sjekk at sum av sortert array er lik sum av originalt array

``` c
// Tests -------------------------------------
// Check if sorted correctly
for (int i = 1; i < size; i++) {
    if (array[i] < array[i - 1]) {
        printf("Error: Array not sorted correctly for size %d\n", size);
        break;
    }
}
// Check for sum consistency
long sum_original = 0, sum_sorted = 0;
for (int i = 0; i < size; i++) {
    sum_original += array_original[i];
    sum_sorted += array[i];
}
if (sum_original != sum_sorted) {
    printf("Error: Sum mismatch for size %d\n", size);
    break;
}
// ---------------------------------------------
```

- [x] Programmet sorterer i tall opp til 1 000 000 elementer, på rimelig tid.

``` bash
Size: 1000000  | book 9.687041 seconds | redo 9.656452 seconds | improved 0.068800 seconds | no duplicates 0.220841 seconds
```

- [ ] Programmet må kunne sortere en million med mange duplikater på rimelig tid `(i & 1 ? 42 : rand() % 100)`

    - *Her klarer ikke programmet å sortere en million elementer på rimelig tid, men her kan jeg ikke konkludere rett ved tanke på det at jeg bruker en gammel laptop til min bror kan være en medvirkende faktor. Men vi kan tydelig se resultatene om man bare kjører opp til  100 000 elementer.*

``` bash
Size: 100000   | book 2.336140 seconds | redo 2.331660 seconds | improved 0.019678 seconds | no duplicates 0.012849 seconds
```

I koden har jeg en variant der den kjører duplikat annenhver gang, en der den kjører en tilfeldig fylt tabell opp til tallet 100 *som gir naturlig duplikater* i store mengder, og en der det ikke finnes duplikater, for å få rett data til algoritmene. Om du mener at det ikke er tilfelle at min pc er treg, men er en annen feil i koden, så er jeg åpen for tilbakemeldinger på hva som kan forbedres.

*I programmet er det en variabel `include_every_other` som styrer om den skal ha egen duplikat annen-hver gang, for testing selv.*

- [x] Etter sortering skal programmet derreter sortere tabellen på nytt usen å få en O(n^2) oppførsel.

``` bash
| book 1.028633 seconds | redo 0.995317 seconds | 
```

*Om du ser på koden min i `split()` funksjonen så har jeg et spesieltilfelle på valg av pivit når den er sortert, som gjør at den ikke får O(n^2) oppførsel.*

``` c
if (array[left] <= array[right]) {

    // If already sorted, pick a random pivot to avoid worst-case [O =/= (n^2)]
    pivot_index = left + rand() % (right - left + 1);
} else {
    pivot_index = median3sort(array, left, right);
}
```

*Før jeg la inn denne if-setningen, så fikk jeg O(n^2) oppførsel på sortert tabell.*

## Sorteringsoppgave 3; quicksort med egen forbedring

- [x] Quicksort uten forbedring, på tabell med mange duplikater
- [x] Quicksort med forbedring, på tabell med mange duplikater
    - Ja her kan vi se drastisk forbedring på tid.
- [x] Quicksort med forbedring, på tabell uten duplikater
    - Her er det ikke like stor forskjell, men det er fortsatt en forbedring i større summer.

*Alt av data ser du øverst i oppgave i bash-output.*