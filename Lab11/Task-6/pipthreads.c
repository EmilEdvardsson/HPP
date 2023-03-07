/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4
#define INTERVALS 500000000

double sum;
pthread_mutex_t lock;

void* calculate_pi(void* arg){
  int *start = (int*)arg;
  int end = *start + INTERVALS/NUM_THREADS;
  double dx, x;
  double local_sum = 0.0;

  dx = 1.0/INTERVALS;
  //printf("start = %d\n", start);
  for (int i = *start; i < end; i++) {
    x = dx*(i-0.5);
    local_sum += dx*4.0/(1.0 + x*x);
  }
  pthread_mutex_lock(&lock);
  sum += local_sum;
  pthread_mutex_unlock(&lock);

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int start[NUM_THREADS];
  //int i;
  //const int intervals = 500000000;
  //double sum, dx, x;

  //dx  = 1.0/intervals;
  //sum = 0.0;

  //for (i = 1; i <= intervals; i++) { 
  //  x = dx*(i - 0.5);
  //  sum += dx*4.0/(1.0 + x*x);
  //}

  pthread_mutex_init(&lock, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    start[i] = i*INTERVALS/NUM_THREADS + 1;
    printf("i = %d, intervals = %d, num_threads = %d, start[i] = %d\n", i, INTERVALS, NUM_THREADS, start[i]);
    pthread_create(&threads[i], NULL, calculate_pi, (void*)&start[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&lock);


  printf("PI is approx. %.16f\n",  sum);
  printf("Difference to 'real' pi = %f\n", fabs(sum - M_PI));

  return 0;
}
