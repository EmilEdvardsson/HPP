#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 8
#define INTERVALS 500000000

double sums[NUM_THREADS];

void* calculate_pi(void* arg){
  int *start = (int*)arg;
  int end = *start + INTERVALS/NUM_THREADS;
  double dx, x;
  double local_sum = 0.0;

  dx = 1.0/INTERVALS;
  for (int i = *start; i < end; i++) {
    x = dx*(i-0.5);
    local_sum += dx*4.0/(1.0 + x*x);
  }
  sums[*start/(INTERVALS/NUM_THREADS)] = local_sum;

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int start[NUM_THREADS];
  double sum = 0.0;

  for (int i = 0; i < NUM_THREADS; i++) {
    start[i] = i*INTERVALS/NUM_THREADS + 1;
    pthread_create(&threads[i], NULL, calculate_pi, (void*)&start[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    sum += sums[i];
  }

  printf("PI is approx. %.16f\n",  sum);
  printf("difference to 'real' pi = %f\n", fabs(sum-M_PI));

  return 0;
}
