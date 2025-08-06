#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "mpmc_queue.h"

#define PRODUCERS_COUNT 2
#define CONSUMERS_COUNT 2

MPMCQueue queue;

void* Producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 10; i++) {
        int* value = malloc(sizeof(int));
        *value = i + id * 100;

        printf("Writer %d: write %d\n", id, *value);

        queue_push_back(&queue, value);

        usleep(100000);
    }

    return NULL;
}

void* Consumer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 10; i++) {
        int* value = queue_pop_front(&queue);

        printf("Reader %d: read %d\n", id, *value);

        free(value);

        usleep(150000);
    }

    return NULL;
}

int main() {
    pthread_t thread_producers[PRODUCERS_COUNT];
    pthread_t thread_consumers[CONSUMERS_COUNT];

    int producers_ids[PRODUCERS_COUNT];
    int consumers_ids[CONSUMERS_COUNT];

    for (int i = 0; i < PRODUCERS_COUNT; i++) {
        producers_ids[i] = i;

        pthread_create(&thread_producers[i], NULL, Producer, &producers_ids[i]);
    }

    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        consumers_ids[i] = i;

        pthread_create(&thread_consumers[i], NULL, Consumer, &consumers_ids[i]);
    }

    for (int i = 0; i < PRODUCERS_COUNT; i++) {
        pthread_join(thread_producers[i], NULL);
    }

    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        pthread_join(thread_consumers[i], NULL);
    }

    return 0;
}
