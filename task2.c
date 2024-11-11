#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10
#define NUM_THREADS 2

int array[ARRAY_SIZE] = {0, 7, 21, 42, 63, 84, 106};

typedef struct {
    int start;
    int end;
} ThreadData;

void* sumArray(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;
    for (int i = data->start; i < data->end; i++) {
        sum += array[i];
    }
    printf("Sum from index %d to %d is %d\n", data->start, data->end - 1, sum);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int segment_size = ARRAY_SIZE / NUM_THREADS;

    for (long t = 0; t < NUM_THREADS; t++) {
        thread_data[t].start = t * segment_size;
        thread_data[t].end = (t + 1) * segment_size;
        pthread_create(&threads[t], NULL, sumArray, (void*)&thread_data[t]);
    }

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    return 0;
}
