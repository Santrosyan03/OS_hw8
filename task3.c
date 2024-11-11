#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void* printNumbers(void* arg) {
    long thread_id = (long)arg;
    for (int i = 1; i <= 5; i++) {
        printf("Thread %ld: %d\n", thread_id, i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, printNumbers, (void*)t);
        if (rc) {
            printf("Error: Unable to create thread %d\n", rc);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    return 0;
}
