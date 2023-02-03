#include <stdio.h>
#include <stdlib.h>

int main() {
    int integer;
    double dbl;
    char character;
    float floatnum;

    FILE *file;

    file = fopen("little_bin_file", "rb");

    fread(&integer, sizeof(int), 1, file);
    fread(&dbl, sizeof(double), 1, file);
    fread(&character, sizeof(char), 1, file);
    fread(&floatnum, sizeof(float), 1, file);

    printf("%d\n%.8lf\n%c\n%.3f\n", integer, dbl, character, floatnum);
    fclose(file);
    return 0;
}
