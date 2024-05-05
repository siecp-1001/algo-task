#include <stdio.h>

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

int main() {
    int candles_count;
    printf("enter num candels\n");
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

    int result = birthdayCakeCandlesIterative(candles_count, candles);
    printf(" result %d\n", result);

    free(candles);

    return 0;
}
