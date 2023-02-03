#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rows = atoi(argv[1]), n, k;


    int **triangle = (int **) malloc(rows * sizeof(int*));
    for (n = 0; n<rows; n++){
        triangle[n] = (int *) malloc((n+1) * sizeof(int));
    }

    for (n = 0; n < rows; n++){

        for (k = 0; k <= n; k++){
            if (n == k || k == 0){
                triangle[n][k] = 1;
            }
            else {
                triangle[n][k] = triangle[n-1][k-1] + triangle[n-1][k];
            }
        }
    }
    for (n = 0; n < rows; n++){
        for (k = 0; k <= n; k++){
            printf("%d",triangle[n][k]);
        }
        free(triangle[n]);
        printf("\n");
    }
    free(triangle);

    return 0;
}

