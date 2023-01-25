#include <stdio.h>
#include <math.h>

/*Task 5
Program that checks if entered number has a perfect square
*/

int main() {
    double num;
    char op;
    printf("Enter a number: ");
    scanf("%lf", &num);

    if (sqrt(num) == (int)sqrt(num) && (int)sqrt(num)%1 == 0){
        printf("The number has a perfect square which is: %.5lf", sqrt(num));
    } else {
        printf("The number does not have a perfect square which is: %.5lf", sqrt(num));
    }

    return 0;
}

