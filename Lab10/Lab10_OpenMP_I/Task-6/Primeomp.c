#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

int is_prime(int n) {
   int i;
   if (n <= 1) return 0;
   for (i = 2; i <= sqrt(n); i++) {
      if (n % i == 0) return 0;
   }
   return 1;
}


int main(int argc, char** argv) {
   int i, j, count = 0;
   double start, end, totaltime;
   if (argc != 3) {
      printf("Wrong input: Upper limit, N_Threads");
      return 1;
   }
   int m = atoi(argv[1]);
   int n = atoi(argv[2]);
   start = omp_get_wtime();

   #pragma omp parallel for num_threads(n) reduction(+:count)
   for (i = 1; i <= m; i++) {
      //int tid = omp_get_thread_num();
      //printf("Starting thread %d\n", tid);
      if (is_prime(i)) {
         count++;
      }
   }
   end = omp_get_wtime();
   totaltime = end - start;
   printf("Number of prime numbers between 1 and %d: %d\n", m, count);
   printf("Total runtime: %lf seconds\n", totaltime);
   return 0;
}
