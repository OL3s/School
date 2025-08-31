# Oppgave 2 innen rekursiv multiplikasjon.

**Vi skal implementere 2 metoder av rekursiv multiplikasjon.**

### Metode 1:

$
n \cdot x = 
\begin{cases}
x & \text{hvis } n = 1 \\
x + (n-1) \cdot x & \text{hvis } n > 1
\end{cases}
$

### Metode 2:

$
n \cdot x = 
\begin{cases}
x & \text{hvis } n = 1 \\
\frac{n}{2} \cdot (x + x) & \text{hvis } n \text{ er partall} \\
x + \frac{n-1}{2} \cdot (x + x) & \text{hvis } n \text{ er oddetall}
\end{cases}
$

Om vi ser på tilstanden til disse rekursivene når $n \to \infty$ så kan vi observere at:

1. **Metode 1** vil resultere i en lineær vekst, ettersom hvert nivå av rekursjon legger til en konstant verdi av $x$.
2. **Metode 2** vil derimot ha en mer kompleks oppførsel, der den halverer problemet ved hvert nivå av rekursjon, noe som kan føre til en mer effektiv løsning for store verdier av $n$.

Med andre ord, så vil dette si at:

- $\text{Metode 1}: \Theta(n)$

- $\text{Metode 2}: \Theta(\log n)$

## Resultater fra kodekjøring

Jeg har prøvd ut forskjellige verdier for n. Men tror jeg snubler på et problem, der minne fra stacken fylles opp ved store verdier av n, og jeg har en pc med begrenset minne. Dette fører til at programmet krasjer når jeg prøver å kjøre metode 1 med lavere verdier. Samt så har jeg prøvd å kjøre metode 2 med så høy int som mulig, dette ved å kjøre verdien INT_MAX/x. for å få en så høy verdi som mulig som pcen kan kalkulere.

***I koden har jeg et dynamisk felt for å sette inn verdier:***
``` C
// dynamic values - to test different values and outcomes
float x = 3.5;
int n[3] = {1, 200, INT_MAX/x+1}; // values to test
int ignore_method_1 = 0;
```

disse verdiene kan endres slik man vil, jeg valgte å ha verdiene `hard-coded` i hovedsak for å kan ha `INT_MAX` som en testverdi. Selv om det gjør testing mere slitsomt da man må kompilere kode for hvert nye forsøk med nye verdier.

**Resultater fra testing**

De faktiske resultetene var at tidene ble 0.0000 sekunder for alle testene. Grunner til dette:
1. Verdiene jeg testet for metode en kunne ikke være høy pa grunn av lavt minne på pc.
2. På metode 2 så ga det 0.0000 sekunder på alle verdier, inkludert `INT_MAX/x+1`.

Jeg har brukt denne metoden før for å kalkulere til, men det er noe feil med selve metoden jeg har brukt til å kalkulere tiden. Men det var et par ganger når jeg kjørte at det var 0.00010 sekunder. Så jeg klarer ikke å lage noen gode tabeller. (prøvde også å legge inn `%.10f` for å få flere desimaler)

Gi gjerne tilbakemelding om du har noen forslag til en annen metode for å kalkulere tiden. Og om å bruke `.md` format er greit, eller om du trenger at jeg konverterer dette til et annet format som `.PDF`.