#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#endif


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
   //printf("Enter the upper limit: ");
   //scanf("%d", &m);
   if (argc != 3) {
      printf("Wrong input: Upper limit, N_Threads");
      return 1;
   }
   int m = atoi(argv[1]);
   int n = atoi(argv[2]);
   #ifdef _OPENMP
   start = omp_get_wtime();
   omp_set_num_threads(n);
   #pragma omp parallel for reduction (+:count)
   for (i = 0; i < n; i++) {
      printf("Starting thread %d\n", i);
      for (j = omp_get_thread_num(); j <= m; j += n){
         if (is_prime(j)) {
            count = count + 1;
         }
      }
   }
   end = omp_get_wtime();
   totaltime = end - start;
   printf("Total runtime: %lf seconds\n", totaltime);
   #else
   for (j = 0; j <= m; j++){
      if (is_prime(j)) {
         count = count + 1;
      }
   }
   #endif
   printf("Number of prime numbers between 1 and %d: %d\n", m, count);
   return 0;
}
