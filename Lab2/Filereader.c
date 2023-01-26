#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char filename[100];
    double price;
    char product[50];
    char junk[256];
    if (argc < 2) {
        printf("Error: Please provide a file name as an argument.\n");
        return 1;
    }
    strcpy(filename, argv[1]);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    printf("Product\tPrice\n");
    fscanf(file, "%s", junk);
    while (fscanf(file, "%s %lf", product, &price) == 2) {
        printf("%s\t%.2f\n", product, price);
    }
    fclose(file);
    return 0;
}


