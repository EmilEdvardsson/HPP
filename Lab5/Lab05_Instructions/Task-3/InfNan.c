#include <stdio.h>
#include <math.h>

int main() {
    double num = 1.0;
    double prev_num;
    for (int i = 0; i < 300; i++) {
        prev_num = num;
        num *= 100;
        if (num == INFINITY) {
            printf("INF reached at iteration %d\n", i);
            break;
        }
        //printf("%.30f\n", num);
    }

    double exponent = log2(prev_num);

    printf("Exponent ~= %f\n", exponent);

    double sqrt_neg = sqrt(-1.0);
    if (isnan(sqrt_neg)) {
        printf("sqrt(-1.0) is NaN\n");
    }

    double inf = INFINITY;
    printf("INF = %.30f\n", inf + 1.0);
    printf("INF + 1.0 = %.30f\n", inf + 1.0);

    double nan = sqrt_neg;
    printf("NaN = %.30f\n", nan);
    printf("NaN + 1.0 = %.30f\n", nan + 1.0);

    return 0;
}
