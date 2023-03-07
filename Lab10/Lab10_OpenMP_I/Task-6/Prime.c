#include <stdio.h>
#include <math.h>

int is_prime(int n) {
   int i;
   if (n <= 1) return 0;
   for (i = 2; i <= sqrt(n); i++) {
      if (n % i == 0) return 0;
   }
   return 1;
}


int main() {
   int m, i, count = 0;
   printf("Enter the upper limit: ");
   scanf("%d", &m);

   for (i = 2; i <= m; i++) {
      if (is_prime(i)) {
         count++;
      }
   }
   printf("Number of prime numbers between 1 and %d: %d\n", m, count);

   return 0;
}
