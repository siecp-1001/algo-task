#include <stdio.h>


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

int main() {
    int candles_count;
    printf("enter num candels\n");
    scanf("%d", &candles_count);

    int *candles = (int *)malloc(candles_count * sizeof(int));
    if (candles == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("enter camdels\n");

    for (int i = 0; i < candles_count; i++) {
        scanf("%d", &candles[i]);
    }

    int result = birthdayCakeCandlesDivideConquer(candles_count, candles);
    printf(" result %d\n", result);

    free(candles);

    return 0;
}
