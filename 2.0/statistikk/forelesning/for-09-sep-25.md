## For-09-sep-25

### Binomiske forsøk og binomisk sannsynlighetsfordeling

- **Binomisk forsøksrekke og Binomisk fordeling**
- **Binomisk forsøksrelle og ...**

***Binomisk forsøksrekke og binomisk fordeling***
- Suksess eller "ikke-suksess" / "fiasko"
- $P(\text{suksess}) = p$
- Alle delforsøkene er uavhengige
- Typisk kjennetegn enten-eller
- $n$ uavhengige forsøk

**Binomisk forsøksrelle og binomisk fordeling**

*eks 1: kaster en terning $n$ ganger, og teller opp antall 6-ere*
- $n = \text{antall kast}$
- $p = P(6) = \frac{1}{6}$
- $X = \text{antall 6-ere på } n \text{ kast}$
- $X \sim \mathrm{Bin}(n, p)$
- $P(X = k) = {n \choose k} p^k (1-p)^{n-k}$
- $E(X) = np$
- $\mathrm{Var}(X) = np(1-p)$

*eks 1: Kaster 3 terninger og teller opp antall 6ere*
- $p = P(A) = \frac{1}{6}$
- $n = 3$
- $X = \text{antall 6ere på 3 kast}$
- $S = \{AAA, AAF, AFA, FAA, AFF, FAF, FFA, FFF\}$

$X \sim \mathrm{Bin}(3, \frac{1}{6})$
- $P(X = 0) = {3 \choose 0} \left(\frac{1}{6}\right)^0 \left(\frac{5}{6}\right)^3 = \frac{125}{216}$
- $P(X = 1) = {3 \choose 1} \left(\frac{1}{6}\right)^1 \left(\frac{5}{6}\right)^2 = \frac{75}{216}$
- $P(X = 2) = {3 \choose 2} \left(\frac{1}{6}\right)^2 \left(\frac{5}{6}\right)^1 = \frac{15}{216}$
- $P(X = 3) = {3 \choose 3} \left(\frac{1}{6}\right)^3 \left(\frac{5}{6}\right)^0 = \frac{1}{216}$

$\{AAA\} = P(X=3) = \frac{1}{6^3} = \frac{1}{216}$

Formel:  
$P(X=k) = {n \choose k} p^k (1-p)^{n-k}$

Fordeling $u = E(X) = np = 3 \cdot \frac{1}{6} = \frac{1}{2}$  
$\mathrm{Var}(X) = np(1-p) = 3 \cdot \frac{1}{6} \cdot \frac{5}{6} = \frac{15}{36} = \frac{5}{12}$

*eks2: en flervalgsoppgave består av 10 spørsmål. Hvert spørsmål har 5 svaralternativer, hvorav 1 er riktig.*
- $n = 10$
- $p = P(\text{riktig svar}) = \frac{1}{5}$
- $X = \text{antall riktige svar}$
- $X \sim \mathrm{Bin}(10, \frac{1}{5})$
- $P(X = k) = {10 \choose k} \left(\frac{1}{5}\right)^k \left(\frac{4}{5}\right)^{10-k}$
- $E(X) = 10 \cdot \frac{1}{5} = 2$
- $\mathrm{Var}(X) = 10 \cdot \frac{1}{5} \cdot \frac{4}{5} = \frac{8}{5} = 1.6$
- I $P(X \leq 4) = 1 - P(X \leq 3) = 1 - 0.8791 = 0.1209$
- Eller bruk F(X) i tabell
- $(X \leq 4) = 1 - P(X \leq 3) = 1 - 0.8791 = 0.1209$
- $P(X \leq 3) = P(X=0) + P(X=1) + P(X=2) + P(X=3)$, som kan skrives som en sum:
- $\sum_{x=0}^{3} {10 \choose x} \left(\frac{1}{5}\right)^x \left(\frac{4}{5}\right)^{10-x}$
- Lærer viser til tabell med ferdige verdier for $X \sim bin(n,p)$
- $P(X \leq k)$ for ulike $n$ og $p$
- $\sigma^2 = \mathrm{Var}(X) = \sum n (n-u)^2 P(X=n) = np(1-p) = 10\cdot 2(1-.2) = 1.60 = \sqrt{1.60} = 1.26$

d. hva er P(X \leq 4 | X \leq 2)
- $P(X \leq 4 | X \leq 2) = \frac{P(X \leq 4 \cap X \leq 2)}{P(X \leq 2)} = \frac{P(X \leq 2)}{P(X \leq 2)} = 1$
- $P(X \leq 4 | X \leq 2) = \frac{0.1219}{ 1 - P(X \leq 1)} = \frac{0.1219}{1 - 0.1937} = \frac{0.1219}{1-0.376} = 0.1949$

**Binomisk fordeling og Geometrisk fordeling**

- $X \sim \text{Geom}(p)$
- $P(X = k) = (1-p)^{k-1} p$
    - for $k = 1, 2, 3, ...$
- $F(k) = P(X \leq k) = 1 - (1-p)^k$
- $E(X) = \frac{1}{p}$
- $\mathrm{Var}(X) = \frac{1-p}{p^2}$
- $X = \text{antall forsøk til første suksess}$

$P(X = 1) = p \cdot (1-p)^{1-1} = p$

For eksempel, hvis $p = \frac{1}{6}$:
$P(X = 1) = \frac{1}{6} \cdot \left(\frac{5}{6}\right)^{0} = \frac{1}{6}$
