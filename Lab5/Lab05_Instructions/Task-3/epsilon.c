#include <stdio.h>

int main() {
    double epsilon = 1.0;
    int i = 0;
    double result;
    while (1 + epsilon > 1) {
        result = 1 + epsilon;
        printf("At iteration %d: 1 + %e = %e (result > 1)\n", i, epsilon, result);
        epsilon *= 0.5;
        i++;
    }
    printf("At iteration %d: 1 + %e = %e (result <= 1)\n", i, epsilon, result);

    return 0;
}
