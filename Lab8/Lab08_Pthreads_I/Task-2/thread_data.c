#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  double *data = (double *)arg;
  printf("Sum = %lf\n", data[0]+data[1]+data[2]);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  double data_for_thread[3];
  data_for_thread[0] = 5.7;
  data_for_thread[1] = 9.2;
  data_for_thread[2] = 1.6;

  double data_for_thread_B[3];
  data_for_thread_B[0] = 1.7;
  data_for_thread_B[1] = 3.8;
  data_for_thread_B[2] = 1.0;

  /* Start thread(s). */
  pthread_t thread;
  pthread_t thread_B;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, data_for_thread);
  printf("the main() function now calling pthread_create_B().\n");
  pthread_create(&thread_B, NULL, the_thread_func, data_for_thread_B);
  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);

  return 0;
}
