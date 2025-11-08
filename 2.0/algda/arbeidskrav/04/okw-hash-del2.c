/*
  Del 2: Åpen adressering (linear probing og double hashing)

  - Genererer unike tilfeldige tall (uten duplikater), stokker dem
  - Kjører eksperimenter for fyllingsgrader: 50%, 80%, 90%, 99%, 100%
  - Teller kollisjoner (0 hvis settes rett på h1-posisjon, ellers antall forsøk)
  - Tar tiden for hvert eksperiment
  - For double hashing: pos = pos + step; wrap uten kostbar modulo i løkka
  - Sikrer at tabellstørrelse er et primtall (viktig for double hashing)
  - Deler av koden for komplex tidsmåling og tilfeldige tall er inspirert og deler kopiert fra ChatGPT-5
  - Ellers brukt deler av Co-Pilot forslag til å finne struktur for eksperimentene
*/

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define DEFAULT_TABLE_SIZE 1000003UL  // standard: a prime ~ 1e6
#define DEFAULT_KEY_COUNT  1000000UL  // number of keys in pool (at least m for 100 % filling)
#define DEFAULT_LOAD_FACTORS {0.50, 0.80, 0.90, 0.99, 1.00} // load factors to test

typedef enum { SLOT_EMPTY = 0, SLOT_USED = 1 } SlotState;

typedef struct {
    uint64_t *slots;   // stores the keys
    uint8_t  *state;   // 0=empty, 1=used
    size_t size;       // table size m
    size_t count;      // number of inserted keys
} OpenAddrTable;

/* ---------- Prime helpers for double hashing ---------- */
// Check if n is prime (naive method)
static int is_prime_u64(uint64_t n) {
    if (n < 2) return 0;
    if ((n % 2) == 0) return n == 2;
    if ((n % 3) == 0) return n == 3;
    for (uint64_t i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// Find the next prime >= n
static uint64_t next_prime_u64(uint64_t n) {
    if (n <= 2) return 2;
    if ((n % 2) == 0) n++;
    while (!is_prime_u64(n)) n += 2;
    return n;
}

/* ---------- Tidsmåling ---------- */
// Get current time in nanoseconds
static inline uint64_t now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

/* ---------- RNG (xorshift64) ---------- */
// Easy and fast RNG to fetch random numbers (ChatGPT-5)
static inline uint64_t xs64(uint64_t *state) {
    uint64_t x = *state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    *state = x;
    return x;
}

// Return a random number in a given range [lo_inclusive..hi_inclusive]
static inline uint64_t rand_range(uint64_t *state, uint64_t lo_inclusive, uint64_t hi_inclusive) {
    uint64_t span = hi_inclusive - lo_inclusive + 1ULL;
    return lo_inclusive + (xs64(state) % span);
}

/* ---------- Key generation (unique numbers) ---------- */
// Generate n unique random numbers in out[]
static void generate_unique_numbers(uint64_t *out, size_t n, uint64_t seed) {
    // Start at a value and increase by a random step [1..1000] to get a strictly increasing (unique) sequence
    uint64_t rng = seed ? seed : 1ULL;
    uint64_t v = xs64(&rng); // start
    for (size_t i = 0; i < n; i++) {
        uint64_t step = rand_range(&rng, 1ULL, 1000ULL);
        v += step;          // ensures unique numbers
        out[i] = v;
    }
    // Fisher-Yates shuffle to randomize order
    for (size_t i = n; i > 1; i--) {
        size_t j = (size_t)(xs64(&rng) % i);
        size_t k = i - 1;
        uint64_t tmp = out[k];
        out[k] = out[j];
        out[j] = tmp;
    }
}

/* ---------- Hash functions ---------- */
// h1 - primary hash function
static inline size_t h1(uint64_t key, size_t m) {
    return (size_t)(key % (uint64_t)m);
}
// h2 - secondary hash function (for double hashing)
static inline size_t h2(uint64_t key, size_t m) {
    // For prime m: 1 + key % (m-1) is in [1..m-1] and is coprime with m
    return 1 + (size_t)(key % (uint64_t)(m - 1));
}

/* ---------- Table management ---------- */
// Create and initialize a hash table of size m
static OpenAddrTable table_create(size_t m) {
    OpenAddrTable t;
    t.size = m;
    t.count = 0;
    t.slots = (uint64_t*)malloc(sizeof(uint64_t) * m);
    t.state = (uint8_t*)malloc(sizeof(uint8_t) * m);
    if (!t.slots || !t.state) {
        fprintf(stderr, "Error: memory allocation failed for table of size %zu\n", m);
        exit(1);
    }
    memset(t.state, 0, m); // all empty
    return t;
}
// Free the hash table
static void table_free(OpenAddrTable *t) {
    free(t->slots);
    free(t->state);
    t->slots = NULL;
    t->state = NULL;
    t->size = 0;
    t->count = 0;
}

/* ---------- Insert with collision counting ---------- */
// Insert key into table using linear probing
static size_t insert_linear(OpenAddrTable *t, uint64_t key) {
    size_t m = t->size;
    size_t pos = h1(key, m);
    size_t collisions = 0;

    // Ingen kollisjon
    if (t->state[pos] == SLOT_EMPTY) {
        t->slots[pos] = key;
        t->state[pos] = SLOT_USED;
        t->count++;
        return 0;
    }

    // Lineær probing
    do {
        collisions++;
        pos++;
        if (pos == m) pos = 0;
        if (t->state[pos] == SLOT_EMPTY) {
            t->slots[pos] = key;
            t->state[pos] = SLOT_USED;
            t->count++;
            return collisions;
        }
    } while (collisions < m);

    fprintf(stderr, "Error: linear probing failed to insert after %zu probes (table full?)\n", collisions);
    exit(2);
}
// Insert key into table using double hashing
static size_t insert_double_hash(OpenAddrTable *t, uint64_t key) {
    size_t m = t->size;
    size_t pos = h1(key, m);

    if (t->state[pos] == SLOT_EMPTY) {
        t->slots[pos] = key;
        t->state[pos] = SLOT_USED;
        t->count++;
        return 0;
    }

    size_t step = h2(key, m); // only when collision occurs
    size_t collisions = 0;

    // pos = pos + step; wrap without % in loop
    do {
        collisions++;
        pos += step;
        if (pos >= m) pos -= m;
        if (t->state[pos] == SLOT_EMPTY) {
            t->slots[pos] = key;
            t->state[pos] = SLOT_USED;
            t->count++;
            return collisions;
        }
    } while (collisions < m);

    fprintf(stderr, "Error: double hashing failed to insert after %zu probes (table full?)\n", collisions);
    exit(3);
}

/* ---------- Experiments ---------- */
// Run one set of experiments (linear probing and double hashing) for given load factor
static void run_experiment_set(const uint64_t *keys, size_t keysPool, size_t tableSize, double load,
                               uint64_t *outCollLinear, double *outMsLinear,
                               uint64_t *outCollDouble, double *outMsDouble) {
    size_t insertCount = (size_t)(load * (double)tableSize);
    if (insertCount > keysPool) insertCount = keysPool;

    // Linear probing
    OpenAddrTable tl = table_create(tableSize);
    uint64_t t0 = now_ns();
    uint64_t collL = 0;
    for (size_t i = 0; i < insertCount; i++) {
        collL += insert_linear(&tl, keys[i]);
    }
    uint64_t t1 = now_ns();
    *outCollLinear = collL;
    *outMsLinear = (double)(t1 - t0) / 1e6;
    table_free(&tl);

    // Double hashing
    OpenAddrTable td = table_create(tableSize);
    t0 = now_ns();
    uint64_t collD = 0;
    for (size_t i = 0; i < insertCount; i++) {
        collD += insert_double_hash(&td, keys[i]);
    }
    t1 = now_ns();
    *outCollDouble = collD;
    *outMsDouble = (double)(t1 - t0) / 1e6;
    table_free(&td);
}

/* ---------- Utility functions ---------- */
// Print header for the results
static void print_header(size_t tableSize, size_t keysPool, const double *loads, size_t numLoads) {
    printf("=== Del 2: Hashing med åpen adressering ===\n");
    printf("Tabellstørrelse: %zu | Antall nøkler i pool: %zu\n", tableSize, keysPool);
    printf("Fyllingsgrader: ");
    for (size_t i = 0; i < numLoads; i++) {
        printf("%s ", (i == 0) ? "" : ", ");
        printf("%.0f%%", loads[i] * 100.0);
    }
    printf("\n");
    printf("Kollisjoner telles som antall ekstra forsøk etter h1-plass.\n\n");
}

/* ---------- main ---------- */
int main(int argc, char **argv) {
    size_t tableSize = DEFAULT_TABLE_SIZE;
    size_t keysPool  = DEFAULT_KEY_COUNT;
    uint64_t seed    = 1ULL;

    if (argc >= 2) tableSize = (size_t)strtoull(argv[1], NULL, 10);
    if (argc >= 3) keysPool  = (size_t)strtoull(argv[2], NULL, 10);
    if (argc >= 4) seed      = strtoull(argv[3], NULL, 10);

    // Basic checks
    if (tableSize < 3) {
        fprintf(stderr, "Table size must be at least 3\n");
        return 1;
    }

    // Make sure we have a prime number m (important for double hashing)
    uint64_t pm = next_prime_u64((uint64_t)tableSize);
    if (pm != (uint64_t)tableSize) {
        printf("Justerer tabellstørrelse til nærmeste primtall: %zu -> %llu\n",
               tableSize, (unsigned long long)pm);
        tableSize = (size_t)pm;
    }

    // Make sure we fill at least up to 100%
    if (keysPool < tableSize) {
        keysPool = tableSize;
    }

    // Generate unique keys
    uint64_t *keys = (uint64_t*)malloc(sizeof(uint64_t) * keysPool);
    if (!keys) {
        fprintf(stderr, "Error: could not allocate key pool of %zu\n", keysPool);
        return 1;
    }
    generate_unique_numbers(keys, keysPool, seed);

    // Define load factors
    const double loads[] = DEFAULT_LOAD_FACTORS;
    size_t numLoads = sizeof(loads)/sizeof(loads[0]);
    print_header(tableSize, keysPool, loads, numLoads);

    for (size_t i = 0; i < numLoads; i++) {
        uint64_t collL = 0, collD = 0;  // Collision counts     {linear, double}
        double msL = 0.0, msD = 0.0;    // Time in milliseconds {linear, double}

        run_experiment_set(keys, keysPool, tableSize, loads[i], &collL, &msL, &collD, &msD);

        printf("- Fyllingsgrad %.0f%%:\n", loads[i] * 100.0);
        printf("  Linear probing   -> kollisjoner: %llu, tid: %.2f ms\n",
               (unsigned long long)collL, msL);
        printf("  Double hashing   -> kollisjoner: %llu, tid: %.2f ms\n\n",
               (unsigned long long)collD, msD);
    }

    free(keys);
    return 0;
}