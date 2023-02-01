#include <stdio.h>
#include <stdlib.h>

int func(){
    return 1;
}

int main(int argc, char **argv){
    int sum = 2;
    for (int i = 0; i < 1e10; i++){
        sum = sum + func();
    }
    printf("Sum = %d", sum);
    return 0;
}
