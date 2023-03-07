/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char *argv[]) {

  int i;
  const int intervals = 500000000;
  double sum, dx, x;
  int n_threads = atoi(argv[1]);
  printf("Using %d number of threads.\n", n_threads);

  dx  = 1.0/intervals;
  sum = 0.0;
#pragma omp parallel for num_threads(n_threads) reduction(+:sum)
  for (i = 1; i <= intervals; i++) { 
    x = dx*(i - 0.5);
    sum += dx*4.0/(1.0 + x*x);
  }

  printf("PI is approx. %.16f\n",  sum);

  return 0;
}
