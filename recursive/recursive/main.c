#include <stdio.h>

int countTallestCandlesRecursive(int *candles, int index, int max_height) {
    if (index < 0)
        return 0;

    int count = countTallestCandlesRecursive(candles, index - 1, max_height);
    if (candles[index] > max_height)
        return count + 1;
    else if (candles[index] == max_height)
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

int main() {
    int candles_count;
    printf("num of candels\n");
    scanf("%d", &candles_count);

    int *candles = (int *)malloc(candles_count * sizeof(int));
    if (candles == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
     printf("enter candels\n");
    for (int i = 0; i < candles_count; i++) {
        scanf("%d", &candles[i]);
    }

    int result = birthdayCakeCandlesRecursive(candles_count, candles);
    printf("result  %d\n", result);

    free(candles);

    return 0;
}
