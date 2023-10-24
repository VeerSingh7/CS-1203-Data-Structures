#include <stdio.h>
#include <stdbool.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Find the next lexicographically greater permutation
bool next_permutation(int* arr, int n) {
    // Step 1: Find the largest index k such that arr[k] < arr[k+1]
    int k = n - 2;
    while (k >= 0 && arr[k] >= arr[k + 1]) {
        k--;
    }

    if (k == -1) {
        // This is the last permutation
        return false;
    }

    // Step 2: Find the largest index l > k such that arr[k] < arr[l]
    int l = n - 1;
    while (arr[k] >= arr[l]) {
        l--;
    }

    // Step 3: Swap arr[k] and arr[l]
    swap(&arr[k], &arr[l]);

    // Step 4: Reverse the sequence from arr[k+1] up to and including the final element arr[n-1]
    int start = k + 1, end = n - 1;
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
    
    return true;
}

int main() {
    int n;
    printf("Enter the value of n (1 <= n <= 8): ");
    scanf("%d", &n);

    if (n < 1 || n > 8) {
        printf("Invalid input. Ensure 1 <= n <= 8.\n");
        return 1;
    }

    int arr[8];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Print first permutation
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    while (next_permutation(arr, n)) {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}
