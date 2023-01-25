#include <stdio.h>

int main()
{
    int a;
    int b;
    printf("Height: ");
    scanf("%d", &a);
    printf("Width: ");
    scanf("%d", &b);
    printf("a = %d\n", a);
    printf("b = %d\n", b);

    for (int i = 0; i<a; i++){
        for (int j = 0; j<b; j++){
            if (i == 0 || i == a-1 || j == 0 || j == b-1){
                printf("*");

                if (j == b-1){
                    printf("\n");
                }
            }
            else {
                printf(".");
            }
        }
    }
    return 0;
}
