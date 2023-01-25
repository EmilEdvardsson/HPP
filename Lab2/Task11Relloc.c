#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *arr = NULL;
    int n = 0, size = 0, sum = 0;
    int input;

    while (scanf("%d", &input) == 1) {
        if (n == size) {
            size += 10;
            arr = realloc(arr, size * sizeof(int));
        }
        arr[n++] = input;
    }

    print_array(arr, n);
    for (int i = 0; i < n; i++)
        sum += arr[i];
    printf("Sum: %d\n", sum);

    free(arr);
    return 0;
}
