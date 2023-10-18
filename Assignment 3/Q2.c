#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 1000
#define TEST_RUNS 100

// Function for Insertion Sort
void insertion_sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function for Bubble Sort
void bubble_sort(int arr[], int n) {
    int i, j, temp;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    int arr1[SIZE], arr2[SIZE];
    clock_t start, end;
    double insertion_times[TEST_RUNS], bubble_times[TEST_RUNS];

    double insertion_total_time = 0, bubble_total_time = 0;
    double insertion_min_time = 9999999, insertion_max_time = 0;
    double bubble_min_time = 9999999, bubble_max_time = 0;

    for (int k = 0; k < TEST_RUNS; k++) {
        // Filling the array with random numbers
        for (int i = 0; i < SIZE; i++) {
            arr1[i] = rand() % 1000;
            arr2[i] = arr1[i];
        }

        start = clock();
        insertion_sort(arr1, SIZE);
        end = clock();
        insertion_times[k] = ((double) (end - start)) / CLOCKS_PER_SEC;
        insertion_total_time += insertion_times[k];
        if (insertion_times[k] < insertion_min_time) insertion_min_time = insertion_times[k];
        if (insertion_times[k] > insertion_max_time) insertion_max_time = insertion_times[k];

        start = clock();
        bubble_sort(arr2, SIZE);
        end = clock();
        bubble_times[k] = ((double) (end - start)) / CLOCKS_PER_SEC;
        bubble_total_time += bubble_times[k];
        if (bubble_times[k] < bubble_min_time) bubble_min_time = bubble_times[k];
        if (bubble_times[k] > bubble_max_time) bubble_max_time = bubble_times[k];
    }

    printf("Size of Array: %d\n\n", SIZE);
    printf("Number of Test Runs: %d\n\n", TEST_RUNS);
    printf("---------------- THEORETICAL TIME COMPLEXITIES ----------------\n");
    printf("Algorithm          | Best Case | Average Case | Worst Case  \n");
    printf("-------------------|-----------|--------------|-------------\n");
    printf("Insertion Sort     | O(n)      | O(n^2)       | O(n^2)      \n");
    printf("Bubble Sort        | O(n)      | O(n^2)       | O(n^2)      \n");
    printf("---------------------------------------------------------------\n\n");

    printf("--------- EXPERIMENTAL DATA ANALYSIS ---------\n");
    printf("Algorithm          | Min Time  | Max Time  | Average Time\n");
    printf("-------------------|----------|----------|-------------\n");
    printf("Insertion Sort     | %f | %f | %f\n", insertion_min_time, insertion_max_time, insertion_total_time / TEST_RUNS);
    printf("Bubble Sort        | %f | %f | %f\n", bubble_min_time, bubble_max_time, bubble_total_time / TEST_RUNS);
    printf("----------------------------------------------\n");
    // Conclusion
    printf("\n------------------- CONCLUSION -------------------\n");
    if ((insertion_total_time / TEST_RUNS) < (bubble_total_time / TEST_RUNS)) {
        printf("Based on the experimental data, Insertion Sort is relatively faster than Bubble Sort for the given dataset.\n");
    } else if ((insertion_total_time / TEST_RUNS) > (bubble_total_time / TEST_RUNS)) {
        printf("Based on the experimental data, Bubble Sort is relatively faster than Insertion Sort for the given dataset.\n");
    } else {
        printf("Based on the experimental data, both Insertion Sort and Bubble Sort have comparable performance for the given dataset.\n");
    }
    printf("-------------------------------------------------\n");
return 0;
}