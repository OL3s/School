# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// A simple swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Median-of-three method from the book
int median3sort(int *array, int left, int right) {
    int center = (left + right) / 2;

    if (array[left] > array[center]) swap(&array[left], &array[center]);
    
    if (array[center] > array[right]) {
        swap(&array[center], &array[right]);
        if (array[left] > array[center]) {
            swap(&array[left], &array[center]);
            if (array[left] > array[center]) swap(&array[left], &array[center]);
        }
    }

    return center;
}

// Partitioning method
int split(int *array, int left, int right) {
    int pivot_index = median3sort(array, left, right);
    int pivot_value = array[pivot_index];
    swap(&array[pivot_index], &array[right - 1]);
    int store_index = left;

    for (int i = left; i < right - 1; i++) {
        if (array[i] < pivot_value) {
            swap(&array[i], &array[store_index]);
            store_index++;
        }
    }
    swap(&array[store_index], &array[right - 1]);
    return store_index;
}

// Quicksort method from the book
void quicksort(int *array, int left, int right) {
    if (right - left > 2) {
        int pivot = split(array, left, right);
        quicksort(array, left, pivot - 1);
        quicksort(array, pivot + 1, right);
    } else {
        median3sort(array, left, right);
    }
}

// Struct to save statistics
struct Statistics {
    double time_taken;
    int num_elements;
};

// Main function
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

    printf("\nStatistics default (book) quicksort:\n");
    for (int s = 0; s < size_count; s++) {
        printf("Size: %-8d | %.6f seconds\n", stats[s].num_elements, stats[s].time_taken);
    }

    return 0;
}