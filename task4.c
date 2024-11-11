#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 5

int numbers[ARRAY_SIZE] = {0, 7, 21, 42, 63};

void* calculateSquare(void* arg) {
    int num = *(int*)arg;
    int square = num * num;
    printf("Square of %d is %d\n", num, square);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[ARRAY_SIZE];
    int rc;

    for (long t = 0; t < ARRAY_SIZE; t++) {
        rc = pthread_create(&threads[t], NULL, calculateSquare, (void*)&numbers[t]);
        if (rc) {
            printf("Error: Unable to create thread %d\n", rc);
            exit(-1);
        }
    }

    for (long t = 0; t < ARRAY_SIZE; t++) {
        pthread_join(threads[t], NULL);
    }

    return 0;
}
