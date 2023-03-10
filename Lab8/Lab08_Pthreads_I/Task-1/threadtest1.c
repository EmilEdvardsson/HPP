#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  printf("Running the_thread_func\n");
  printf("the_thread_func() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  printf("Result of work in the_thread_func(): sum = %f\n", sum);
  return NULL;
}

void* the_thread_func_B(void* arg) {
  printf("Running the_thread_func_B\n");
  printf("the_thread_func_B() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  printf("Results of work in the_thread_func_B(): sum = %f\n", sum);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread(s). */
  pthread_t thread, threadB;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, NULL);
  pthread_create(&threadB, NULL, the_thread_func_B, NULL);
  printf("main() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  printf("Result of work in main(): sum = %f\n", sum);
  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);
  pthread_join(threadB, NULL);
  printf("the main() function returned from calling pthread_join().\n");

  return 0;
}
