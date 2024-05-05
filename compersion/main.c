#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int countTallestCandlesRecursive(int *candles, int index, int max_height) {
    if (index < 0)
        return 0;

    int count = countTallestCandlesRecursive(candles, index - 1, max_height);
    if (candles[index] > max_height || candles[index] == max_height)
        return count + 1;
    else
        return count;
}

int birthdayCakeCandlesRecursive(int candles_count, int *candles) {
    int max_height = 0;
    for (int i = 0; i < candles_count; i++) {
        if (candles[i] > max_height)
            max_height = candles[i];
    }
    return countTallestCandlesRecursive(candles, candles_count - 1, max_height);
}

int birthdayCakeCandlesIterative(int candles_count, int* candles) {
    int max_height = 0;
    int count = 0;
    for (int i = 0; i < candles_count; i++) {
        if (candles[i] > max_height) {
            max_height = candles[i];
            count = 1;
        } else if (candles[i] == max_height) {
            count++;
        }
    }
    return count;
}

int merge(int *arr, int left, int mid, int right, int max_height) {
    int i, j, k;
    int count = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] > R[j]) {
            arr[k++] = L[i++];
            if (L[i - 1] == max_height)
                count++;
        } else {
            arr[k++] = R[j++];
            if (R[j - 1] == max_height)
                count++;
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
        if (L[i - 1] == max_height)
            count++;
    }
    while (j < n2) {
        arr[k++] = R[j++];
        if (R[j - 1] == max_height)
            count++;
    }
    return count;
}

int mergeSort(int *arr, int left, int right, int max_height) {
    int count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += mergeSort(arr, left, mid, max_height);
        count += mergeSort(arr, mid + 1, right, max_height);
        count += merge(arr, left, mid, right, max_height);
    }
    return count;
}

int birthdayCakeCandlesDivideConquer(int candles_count, int *candles) {
    int max_height = 0;
    for (int i = 0; i < candles_count; i++) {
        if (candles[i] > max_height)
            max_height = candles[i];
    }
    return mergeSort(candles, 0, candles_count - 1, max_height);
}

void generateRandomArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000 + 1;
    }
}

int main() {
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;

    int sizes[] = {100, 1000, 10000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Size\tRecursive\tIterative\tDivide&Conquer\n");
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int *candles = (int *)malloc(size * sizeof(int));
        if (candles == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        generateRandomArray(candles, size);

        start = clock();
        int result_recursive = birthdayCakeCandlesRecursive(size, candles);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%f\t", size, cpu_time_used);

        start = clock();
        int result_iterative = birthdayCakeCandlesIterative(size, candles);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%f\t", cpu_time_used);

        start = clock();
        int result_divide_conquer = birthdayCakeCandlesDivideConquer(size, candles);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%f\n", cpu_time_used);

        free(candles);
    }

    return 0;
}
