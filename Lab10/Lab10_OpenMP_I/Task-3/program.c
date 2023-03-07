#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void thread_func() {
  int tnum = omp_get_thread_num();
  int numt = omp_get_num_threads();
  //printf("This is inside thread_func()!\n");
  printf("Thread_ID: %d, Threads: %d\n", tnum, numt);
}

int main(int argc, char** argv) {

  if (argc != 2) {
    printf("Wrong input");
    return 1;
  }
  int n = atoi(argv[1]);

#pragma omp parallel num_threads(n)
  {
    thread_func();
  }

  return 0;
}
