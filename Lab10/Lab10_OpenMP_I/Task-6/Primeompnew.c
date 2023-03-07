#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    int limit = sqrt(n);
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s N num_threads\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    int count = 0;

    #pragma omp parallel for num_threads(num_threads) reduction(+:count)
    for (int i = 1; i <= N; i++) {
        if (is_prime(i)) {
            count++;
        }
    }

    printf("Number of primes between 1 and %d: %d\n", N, count);

    return 0;
}
