#ifndef MPMC_QUEUE_H
#define MPMC_QUEUE_H

#include <pthread.h>

#define QUEUE_CAPACITY 1024

typedef struct {
    void* values[QUEUE_CAPACITY];
    int head;
    int tail;
    int size;

    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;

} MPMCQueue;

void queue_init(MPMCQueue* queue);
void queue_destroy(MPMCQueue* queue);

void queue_push_back(MPMCQueue* queue, void* value);
void* queue_pop_front(MPMCQueue* queue);

#endif // MPMC_QUEUE_H
