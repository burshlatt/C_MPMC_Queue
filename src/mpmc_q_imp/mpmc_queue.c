#include <stdio.h>
#include <stdlib.h>

#include "mpmc_queue.h"

void queue_init(MPMCQueue* queue) {
    queue->head = queue->tail = queue->size = 0;

    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_full, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
}

void queue_destroy(MPMCQueue* queue) {
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->not_full);
    pthread_cond_destroy(&queue->not_empty);
}

void queue_push_back(MPMCQueue* queue, void* value) {
    pthread_mutex_lock(&queue->mutex);

    while (queue->size == QUEUE_CAPACITY) {
        pthread_cond_wait(&queue->not_full, &queue->mutex);
    }

    queue->values[queue->tail] = value;
    queue->tail = (queue->tail + 1) % QUEUE_CAPACITY;
    queue->size++;
    
    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->mutex);
}

void* queue_pop_front(MPMCQueue* queue) {
    pthread_mutex_lock(&queue->mutex);

    while (queue->size == 0) {
        pthread_cond_wait(&queue->not_full, &queue->mutex);
    }

    void* value = queue->values[queue->head];
    queue->head = (queue->head + 1) % QUEUE_CAPACITY;
    queue->size--;
    
    pthread_cond_signal(&queue->not_full);
    pthread_mutex_unlock(&queue->mutex);

    return value;
}
