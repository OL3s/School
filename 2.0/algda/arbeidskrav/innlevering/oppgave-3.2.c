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
    int pivot_index;
    if (array[left] <= array[right]) {

        // If already sorted, pick a random pivot to avoid worst-case [O =/= (n^2)]
        pivot_index = left + rand() % (right - left + 1);
    } else {
        pivot_index = median3sort(array, left, right);
    }
    int pivot_value = array[pivot_index];
    swap(&array[pivot_index], &array[right]);
    int store_index = left;

    for (int i = left; i < right; i++) {
        if (array[i] < pivot_value) {
            swap(&array[i], &array[store_index]);
            store_index++;
        }
    }
    swap(&array[store_index], &array[right]);
    return store_index;
}

// Quicksort method from the book
/*
    Made some minor changes cause i found some errors when running with larger arrays. (1 000 000 elements)
*/
void quicksort(int *array, int left, int right) {
    int size = right - left + 1;
    if (size > 2) {
        int pivot = split(array, left, right);
        quicksort(array, left, pivot - 1);
        quicksort(array, pivot + 1, right);
    } else if (size == 2) {
        if (array[left] > array[right]) swap(&array[left], &array[right]);
    } else if (size == 3) {
        median3sort(array, left, right);
    }
}

/*

    Improved quicksort method:
    - Checks for duplicates in the array, and if all elements are equal, it returns immediately.
    - If there are only two elements, it sorts them directly.
    - Otherwise, it proceeds with the standard quicksort algorithm.

*/
// Quicksort improved
void quicksort_new(int *array, int left, int right) {
    int size = right - left + 1;
    if (size <= 1) return;

    // Check for duplicates
    if (array[left] == array[right]) {
        int all_equal = 1;
        for (int i = left + 1; i <= right; i++) {
            if (array[i] != array[left]) {
                all_equal = 0;
                break;
            }
        }
        if (all_equal) return; // Return if all elements are equal
    }

    if (size == 2) {
        if (array[left] > array[right]) swap(&array[left], &array[right]);
        return;
    }

    int pivot = split(array, left, right);
    quicksort_new(array, left, pivot - 1);
    quicksort_new(array, pivot + 1, right);
}

// Struct to save statistics
struct Statistics {
    double time_taken;
    double improved_time;
    int num_elements;
    double time_redo;
    double time_noduplicates;
};

// Main function
int main(int argc, char *argv[]) {
    clock_t start, end;
    int enable_print_listing = argc > 1 && argv[1][0] == '1';
    int sizes[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    int size_count = sizeof(sizes) / sizeof(sizes[0]);
    struct Statistics stats[size_count];
    int include_every_other = 0;

    // Loop over different sizes
    for (int s = 0; s < size_count; s++) {
        int size = sizes[s];
        int *array = malloc(size * sizeof(int));
        int *array_original = malloc(size * sizeof(int));
        int *array_improved = malloc(size * sizeof(int));
        int *array_noduplicates = malloc(size * sizeof(int));
        stats[s].num_elements = size;
        for (int i = 0; i < size; i++) {
            array[i] = (i & 1) ? (include_every_other ? 42 : rand() % 100) : rand() % 100;
            array_original[i] = array[i];
            array_improved[i] = array[i];
        }

        // No duplicates array
        for (int i = 0; i < size; i++) {
            array_noduplicates[i] = i;
        }

        // Shuffle the no-duplicates array
        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(&array_noduplicates[i], &array_noduplicates[j]);
        }

        // Run and time the quicksort
        start = clock();
        quicksort(array, 0, size - 1);
        end = clock();
        stats[s].time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Redo the sort to measure time again
        start = clock();
        quicksort(array, 0, size - 1); // Redo
        end = clock();
        stats[s].time_redo = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Improved quicksort
        start = clock();
        quicksort_new(array_improved, 0, size - 1);
        end = clock();
        stats[s].improved_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Improved without duplicates
        start = clock();
        quicksort_new(array_noduplicates, 0, size - 1);
        end = clock();
        stats[s].time_noduplicates = ((double)(end - start)) / CLOCKS_PER_SEC;


        // Tests -------------------------------------
        // Check if sorted correctly
        for (int i = 1; i < size; i++) {
            if (array[i] < array[i - 1] || array_improved[i] < array_improved[i - 1] || array_noduplicates[i] < array_noduplicates[i - 1]) {
                printf("Error: Array not sorted correctly for size %d\n", size);
                break;
            }
        }
        // Check for sum consistency
        long sum_original = 0, sum_sorted = 0, sum_improved = 0, sum_noduplicates = 0;
        for (int i = 0; i < size; i++) {
            sum_original += array_original[i];
            sum_sorted += array[i];
            sum_improved += array_improved[i];
            sum_noduplicates += array_noduplicates[i];
        }
        if (sum_original != sum_sorted) {
            printf("Error: Sum mismatch for size %d\n", size);
            break;
        }
        // ---------------------------------------------

        // Free allocated memory
        free(array);
        free(array_original);
        free(array_improved);
        free(array_noduplicates);

    }

    // Print statistics
    printf("\nStatistics quicksort\n");
    for (int s = 0; s < size_count; s++) {
        printf("Size: %-8d | book %.6f seconds | redo %.6f seconds | improved %.6f seconds | no duplicates %.6f seconds\n", stats[s].num_elements, stats[s].time_taken, stats[s].time_redo, stats[s].improved_time, stats[s].time_noduplicates);
    }

    return 0;
}