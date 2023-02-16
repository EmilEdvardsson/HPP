#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  int *p = NULL;
  p = (int *)malloc(5 * sizeof(int));
  for (int i; i<5; i++){
    p[i] = i;
  }
  pthread_exit((void *)p);
}

int main() {
  printf("This is the main() function starting.\n");
  int *m = NULL;
  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  if(pthread_create(&thread, NULL, the_thread_func, NULL) != 0) {
    printf("ERROR: pthread_create failed.\n");
    return -1;
  }

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  if(pthread_join(thread, (void **)&m) != 0) {
    printf("ERROR: pthread_join failed.\n");
    return -1;
  }

  //Access array
  for (int i=0; i<5; i++) {
    printf("%d ", m[i]);
  }
  printf("\n");

  free(m);

  return 0;
}
