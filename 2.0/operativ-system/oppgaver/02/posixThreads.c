#include <stdio.h>
#include <pthread.h>
#define NTHREADS 10

pthread_t threads[NTHREADS];


void *go(void *n) {
    printf("Hello from thread %ld\n", (long)n);
    pthread_exit((void *)(100 + (long)n));
}

void *go2(void *n) {
    printf("Hello from thread %ld\n", (long)n);
    if ((long)n == 5)
        sleep(2); // Pause thread 5 execution for 2 seconds
    pthread_exit((void *)(100 + (long)n));
}

int main() {
    long i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)i);

    for (i = 0; i < NTHREADS; i++) {
        long exitValue;
        pthread_join(threads[i], (void *)&exitValue);
        printf("Thread %ld returned with %ld\n", i, exitValue);
    }
    printf("Main thread done.\n");
    return 0;
}

