#include <stdio.h>
#include <time.h>

int without_inline(int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += i;
    }
    return result;
}

inline int with_inline(int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += i;
    }
    return result;
}

int main() {
    int n = 100000000;
    clock_t start, end;

    start = clock();
    for (int i = 0; i < 10*n; i++){
    without_inline(n);
    }
    end = clock();
    printf("Without inline: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < 10*n; i++){
    with_inline(n);
    }
    end = clock();
    printf("With inline: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
