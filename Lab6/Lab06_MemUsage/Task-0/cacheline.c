#include <stdio.h>
#include <time.h>

#define ARRAY_SIZE (1 << 25) // size of the array
#define MAX_STRIDE 50        // maximum stride size

int main() {
  int i, j, k;
  int sum = 0;
  int stride = 1;
  int* a = (int*)malloc(ARRAY_SIZE * sizeof(int));
  double min_time = 99999999;
  int min_stride = 1;

  // initialize the array
  for (i = 0; i < ARRAY_SIZE; i++) {
    a[i] = 1;
  }

  // test different stride sizes
  for (stride = 1; stride <= MAX_STRIDE; stride++) {
    clock_t start = clock();

    // access elements with a stride size
    for (i = 0; i < ARRAY_SIZE; i += stride) {
      sum += a[i];
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Stride size: %d Time elapsed: %lf\n", stride, elapsed);
    if (elapsed < min_time) {
      min_time = elapsed;
      min_stride = stride;
    }
  }

  printf("Minimum time elapsed: %lf with stride size: %d\n", min_time, min_stride);
  free(a);
  return 0;
}
