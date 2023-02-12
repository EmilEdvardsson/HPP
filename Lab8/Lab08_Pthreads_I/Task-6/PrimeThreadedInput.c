#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int m, count = 0;
int num_threads;

int is_prime(int n) {
   int i;
   if (n <= 1) return 0;
   for (i = 2; i <= sqrt(n); i++) {
      if (n % i == 0) return 0;
   }
   return 1;
}

void *thread_primes(void *args) {
   int j, start, end, step;
   int *arg = (int *)args;
   int max = arg[0];
   int thread = arg[1];
   printf("Thread = %d\n", thread);
   if (thread == 0) {
      start = 0;
      end = ceil(max/num_threads);
   } else if (thread + 1 != num_threads) {
      step = ceil(max/num_threads);
      start = thread*step+1;
      end = start + step;
   } else {
      step = ceil(max/num_threads)+1;
      start = thread*step;
      end = max;
   }
   //start = (thread*max)/num_threads + 1;
   //end = (thread+1)*max/num_threads;
   printf("Start: %d, End: %d\n", start, end);
   for (j = start; j <= end; j++) {
      if (is_prime(j)) {
         count++;
      }
   }
}

int main(int argc, char *argv[]) {

   if (argc < 2) {
      printf("Usage: %s <number of threads>\n", argv[0]);
      return 1;
   }
   num_threads = atoi(argv[1]);
   long i;
   pthread_t threads[num_threads];
   printf("Enter the upper limit: ");
   scanf("%d", &m);

   int thread_args[num_threads][2];
   for (i = 0; i < num_threads; i++){
      thread_args[i][0] = m;
      thread_args[i][1] = i;
      pthread_create(&threads[i], NULL, thread_primes, (void *)thread_args[i]);
   }

   for (i = 0; i < num_threads; i++){
      pthread_join(threads[i], NULL);
   }

   printf("Number of prime numbers between 1 and %d: %d\n", m, count);

   return 0;
}
