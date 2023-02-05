#include <stdio.h>
#include <math.h>
#include <pthread.h>

int m, count = 0;

int is_prime(int n) {
   int i;
   if (n <= 1) return 0;
   for (i = 2; i <= sqrt(n); i++) {
      if (n % i == 0) return 0;
   }
   return 1;
}

void *thread_primes(void *args) {
   int i, start, end;
   int *arg = (int *)args;
   int max = arg[0];
   int thread = arg[1];
   printf("Thread = %d\n", thread);
   start = (thread*max)/2 + 1;
   end = (thread+1)*max/2;
   printf("Start: %d, End: %d\n", start, end);
   for (i = start; i <= end; i++) {
      if (is_prime(i)) {
         count++;
      }
   }
}

int main() {
   long i;
   pthread_t threads[2];
   printf("Enter the upper limit: ");
   scanf("%d", &m);

   for (i = 0; i<2; i++){
      pthread_create(&threads[i], NULL, thread_primes, (int *)i);
   }

   for (i = 0; i<2; i++){
      pthread_join(threads[i], NULL);
   }

   printf("Number of prime numbers between 1 and %d: %d\n", m, count);

   return 0;
}
