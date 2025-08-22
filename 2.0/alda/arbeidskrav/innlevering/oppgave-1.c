#include <stdio.h>
#include <limits.h>
#include <time.h>

/*
    Oppgave 1.1
    Algoritme som finner beste kjøps- og salgstidspunkt for maksimal profitt
*/

// Struktur for å lagre beste funn
struct Best {
    int x;
    int length;
    int val;
};

// Funksjon for å beregne lengden på perioden i løkka
int best_length(int x, int xx) {
    return xx - x;
}

struct Best get_best_result(int *p_kurs_d, int *p_count) {
    struct Best best = {0, 0, INT_MIN};
    for (int x = 0; x < *p_count - 1; x++) {
        int sum = 0;
        for (int xx = x + 1; xx < *p_count; xx++) {
            sum += p_kurs_d[xx];
            if (sum > best.val) {
                best.x = x;
                best.length = best_length(x, xx);
                best.val = sum;
            }
        }
    }
    return best;
}

// Hovedfunksjon
int main()
{
    // Start measuring time
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Initialisering av variabler
    int kurs_d[] = {-1, 3, -9, 2, 2, -1, 2, -1, -5};    // Listen
    int count = sizeof(kurs_d) / sizeof(kurs_d[0]);     // Antall elementer i listen

    // Nye verdier for testing av tid
    int test_kurs_d[] = {
        -5, 12, -8, 7, -3, 15, -10, 4, -2, 9, -6, 13, -7, 2, -1, 11, -9, 8, -4, 16,
        -12, 5, -14, 17, -11, 3, -13, 18, -15, 6, -16, 19, -17, 10, -18, 20, -19, 14, -20, 21,
        -21, 8, -22, 13, -23, 6, -24, 15, -25, 9, -26, 7, -27, 12, -28, 5, -29, 11, -30, 4,
        -31, 10, -32, 3, -33, 8, -34, 2, -35, 7, -36, 1, -37, 6, -38, 2, -39, 5, -40, 3,
        -41, 4, -42, 2, -43, 3, -44, 1, -45, 2, -46, 1, -47, 2, -48, 1, -49, 1, -50, 0,
        -52, 1, -54, 0, -56, 1, -58, 0, -60, 1, -62, 0, -64, 1, -66, 0, -68, 1, -70, 0,
        -72, 1, -74, 0, -76, 1, -78, 0, -80, 1, -82, 0, -84, 1, -86, 0, -88, 1, -90, 0,
        -92, 1, -94, 0, -96, 1, -98, 0, -100, 1, -102, 0, -104, 1, -106, 0, -108, 1, -110, 0,
        -112, 2, -114, 1, -116, 3, -118, 2, -120, 4, -122, 3, -124, 5, -126, 4, -128, 6, -130, 5,
        -132, 7, -134, 6, -136, 8, -138, 7, -140, 9, -142, 8, -144, 10, -146, 9, -148, 11, -150, 10,
        -152, 12, -154, 11, -156, 13, -158, 12, -160, 14, -162, 13, -164, 15, -166, 14, -168, 16, -170, 15,
        -172, 17, -174, 16, -176, 18, -178, 17, -180, 19, -182, 18, -184, 20, -186, 19, -188, 21, -190, 20,
        -192, 22, -194, 21, -196, 23, -198, 22, -200, 24, -202, 23, -204, 25, -206, 24, -208, 26, -210, 25,
        -212, 27, -214, 26, -216, 28, -218, 27, -220, 29, -222, 28, -224, 30, -226, 29, -228, 31, -230, 30
    };
    int test_count = sizeof(test_kurs_d) / sizeof(test_kurs_d[0]);

    // Valg av verdier i bruk
    int *p_kurs_d = test_kurs_d;
    int *p_count = &test_count;

    // Finn beste kjøps- og salgstidspunkt
    struct Best best_actual = get_best_result(kurs_d, &count);
    struct Best best_test = get_best_result(test_kurs_d, &test_count);

    // Printing av resultater
    printf("\nOppgave 1: \nFor maksimal profitt, kjoper du paa dag %d\n"
           "deretter venter du %d dager for aa selge\n"
           "Dette gir profitt paa %d.\n\n", 
           best_actual.x+1, best_actual.length, best_actual.val);

    /*
        Oppgave 2

        Tidskompleksitet for algoritmen
        O(n^2)
        Ω(n^2)
        Θ(n^2)

        Algoritmen har en øvre grense på Θ(n^2), fordi den har en dobbel for-løkke.
    */
    printf("Oppgave 2: Tidskompleksitet for algorytmen\n"
           "O(n^2)\n"
           "^(n^2)\n"
           "(-)(n^2)\n"
           "Dette kan vi se ved at naar n -> uendelig\n"
           "At det er 2 for lokker i programvaren\n\n");

    /*
    
        Oppgave 3
        Stresstest av stor liste

    */
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Oppgave 3: Tid brukt for test av stor liste (stresstest)\n"
           "Total tid for hele programmet: %f\n", time_spent);

    clock_gettime(CLOCK_MONOTONIC, &start);
    get_best_result(kurs_d, &count);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Total tid for stresstest av satt liste: %f\n", time_spent);

    clock_gettime(CLOCK_MONOTONIC, &start);
    get_best_result(test_kurs_d, &test_count);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Total tid for stresstest av stor liste: %f\n", time_spent);

    return 0;
}
