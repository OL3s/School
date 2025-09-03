// Quicksort med forbedring
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quicksort(int *array, int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (array[j] < pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;

        quicksort(array, low, i);
        quicksort(array, i + 2, high);
    }
}

int main(void) {
    clock_t start, end;
    int size = 100000;
    int array[size];
    for(int i=0; i<size; i++) {
        array[i] = rand() % 1000000;
    }

    start = clock();
    quicksort(array, 0, size - 1);
    end = clock();

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\nTime taken: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}