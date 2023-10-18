#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 1000
#define TEST_RUNS 100
//Merge sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
//Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
//Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main(){
    int arr1[SIZE], arr2[SIZE], arr3[SIZE];
    clock_t start, end;
    double merge_times[TEST_RUNS], quick_times[TEST_RUNS], heap_times[TEST_RUNS];

    double merge_total_time = 0, quick_total_time = 0, heap_total_time = 0;
    double merge_min_time = 9999999, merge_max_time = 0;
    double quick_min_time = 9999999, quick_max_time = 0;
    double heap_min_time = 9999999, heap_max_time = 0;

    for (int k = 0; k < TEST_RUNS; k++) {
        // Filling the array with random numbers
        for (int i = 0; i < SIZE; i++) {
            int num = rand() % 1000;
            arr1[i] = num;
            arr2[i] = num;
            arr3[i] = num;
        }

        // For Merge Sort
        start = clock();
        merge_sort(arr1, 0, SIZE - 1);
        end = clock();
        merge_times[k] = ((double) (end - start)) / CLOCKS_PER_SEC;
        merge_total_time += merge_times[k];
        if (merge_times[k] < merge_min_time) merge_min_time = merge_times[k];
        if (merge_times[k] > merge_max_time) merge_max_time = merge_times[k];

        // For Quick Sort
        start = clock();
        quick_sort(arr2, 0, SIZE - 1);
        end = clock();
        quick_times[k] = ((double) (end - start)) / CLOCKS_PER_SEC;
        quick_total_time += quick_times[k];
        if (quick_times[k] < quick_min_time) quick_min_time = quick_times[k];
        if (quick_times[k] > quick_max_time) quick_max_time = quick_times[k];

        // For Heap Sort
        start = clock();
        heap_sort(arr3, SIZE);
        end = clock();
        heap_times[k] = ((double) (end - start)) / CLOCKS_PER_SEC;
        heap_total_time += heap_times[k];
        if (heap_times[k] < heap_min_time) heap_min_time = heap_times[k];
        if (heap_times[k] > heap_max_time) heap_max_time = heap_times[k];
    }

    // Printing the results
    printf("Size of Array: %d\n\n", SIZE);
    printf("Number of Test Runs: %d\n\n", TEST_RUNS);
    printf("---------------- THEORETICAL TIME COMPLEXITIES ----------------\n");
    printf("Algorithm          | Best Case | Average Case | Worst Case  \n");
    printf("-------------------|-----------|--------------|-------------\n");
    printf("Merge Sort         | O(nlogn)  | O(nlogn)     | O(nlogn)    \n");
    printf("Quick Sort         | O(nlogn)  | O(nlogn)     | O(n^2)      \n");
    printf("Heap Sort          | O(nlogn)  | O(nlogn)     | O(nlogn)    \n");
    printf("---------------------------------------------------------------\n\n");

    printf("--------- EXPERIMENTAL DATA ANALYSIS ---------\n");
    printf("Algorithm          | Min Time  | Max Time  | Average Time\n");
    printf("-------------------|----------|----------|-------------\n");
    printf("Merge Sort         | %f | %f | %f\n", merge_min_time, merge_max_time, merge_total_time / TEST_RUNS);
    printf("Quick Sort         | %f | %f | %f\n", quick_min_time, quick_max_time, quick_total_time / TEST_RUNS);
    printf("Heap Sort          | %f | %f | %f\n", heap_min_time, heap_max_time, heap_total_time / TEST_RUNS);
    printf("----------------------------------------------\n");

    // Conclusion
    printf("\n------------------- CONCLUSION -------------------\n");
    double average_merge = merge_total_time / TEST_RUNS;
    double average_quick = quick_total_time / TEST_RUNS;
    double average_heap = heap_total_time / TEST_RUNS;

    if (average_merge < average_quick && average_merge < average_heap) {
        printf("Based on the experimental data, Merge Sort is the fastest among the three.\n");
    } else if (average_quick < average_merge && average_quick < average_heap) {
        printf("Based on the experimental data, Quick Sort is the fastest among the three.\n");
    } else {
        printf("Based on the experimental data, Heap Sort is the fastest among the three.\n");
    }
    printf("-------------------------------------------------\n");

    return 0;
}
