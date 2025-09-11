// Quicksort
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

struct Statistics {
    double time_taken;
    int num_elements;
};

int main(int argc, char *argv[]) {
    clock_t start, end;
    int enable_print_listing = argc > 1 && argv[1][0] == '1';
    int sizes[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    int size_count = sizeof(sizes) / sizeof(sizes[0]);
    struct Statistics stats[size_count];

    for (int s = 0; s < size_count; s++) {
        int size = sizes[s];
        int array[size];
        for (int i = 0; i < size; i++) {
            array[i] = rand() % 1000000;
        }

        start = clock();
        quicksort(array, 0, size - 1);
        end = clock();

        if (enable_print_listing) {
            printf("Sorted array of size %d:\n", size);
            for (int i = 0; i < size; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }

        stats[s].time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        stats[s].num_elements = size;
    }

    printf("\nStatistics default quicksort:\n");
    for (int s = 0; s < size_count; s++) {
        printf("Size of array: %-8d | %-12f secounds\n", stats[s].num_elements, stats[s].time_taken);
    }

    return 0;
}