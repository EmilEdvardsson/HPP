#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_hello_world(void *tid) {
  printf("Hello from thread tid = %ld\n", (long)tid);
  pthread_exit(NULL);
}

void *create_thread(void *arg) {
  long tid = (long)arg;
  if (tid == 1) {
    pthread_t thread2, thread3;
    int status;
    printf("In main thread, creating thread2\n");
    status = pthread_create(&thread2, NULL, create_thread, (void *)2);
    if (status != 0) {
      printf("Oops. pthread_create returned error for thread2\n");
      exit(-1);
    }
    //pthread_exit(NULL);
    printf("In main thread, creating thread3\n");
    status = pthread_create(&thread3, NULL, create_thread, (void *)3);
    if (status != 0) {
      printf("Oops. pthread_create returned error for thread3\n");
      exit(-1);
    }
    //pthread_exit(NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    printf("Main thread returning\n");

  } else if (tid == 2) {
    pthread_t thread4, thread5;
    int status;
    printf("In thread2, creating thread4\n");
    status = pthread_create(&thread4, NULL, create_thread, (void *)4);
    if (status != 0) {
      printf("Oops. pthread_create returned error for thread4\n");
      exit(-1);
    }
    printf("In thread2, creating thread5\n");
    //pthread_exit(NULL);
    status = pthread_create(&thread5, NULL, create_thread, (void *)5);
    if (status != 0) {
      printf("Oops. pthread_create returned error for thread5\n");
      exit(-1);
    }
    //pthread_exit(NULL);
    pthread_join(thread4,NULL);
    pthread_join(thread5,NULL);
    printf("thread2 returning\n");
  } else if (tid == 3) {
    pthread_t thread6, thread7;
    int status;
    printf("In thread3, creating thread6\n");
    status = pthread_create(&thread6, NULL, create_thread, (void *)6);
    if (status != 0) {
      printf("Oops. pthread_create returned error for thread6\n");
      exit(-1);
    }
    //pthread_exit(NULL);
    printf("In thread3, creating thread7\n");
    status = pthread_create(&thread7, NULL, create_thread, (void *)7);
    if (status != 0) {
      printf("Oops. pthread_create returned error for thread7\n");
      exit(-1);
    }
    //pthread_exit(NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);
    printf("thread3 returning\n");
  } else {
    printf("Finished with thread%ld\n", (long)tid);
  }
}

int main(int argc, char *argv[]) {
  pthread_t main_thread;
  int status;

  printf("In main, creating main thread...\n");
  status = pthread_create(&main_thread, NULL, create_thread, (void *)1);
  if (status != 0) {
    printf("Oops. pthread_create returned error code %d\n", status);
    exit(-1);
  }
  pthread_exit(NULL);
}
