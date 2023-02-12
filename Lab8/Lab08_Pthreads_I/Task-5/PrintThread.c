#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int thread_index;
} ThreadInfo;

void *printThreadIndex(void *arg) {
    ThreadInfo *info = (ThreadInfo *)arg;
    int index = info->thread_index;
    printf("Thread %d\n", index);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int N;
    if (argc < 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    pthread_t threads[N];
    ThreadInfo info[N];
    for (int i = 0; i < N; i++) {
        info[i].thread_index = i;
        int ret = pthread_create(&threads[i], NULL, printThreadIndex, &info[i]);
        if (ret != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
