// queue.c
// Mitchell Wade
// Feb. 17, 2015
// This program is implementation for a queue in C.

#include <stdlib.h>

typedef struct queue {

    void **array;
    int back;
    int front;
    int maxSize;
    int size;

} Queue;

// Creates a queue
void *queue_new(int numItems) {
    
    Queue *q = (Queue *)malloc(sizeof(Queue));
    
    q->array = (void **)malloc(sizeof(void *)*numItems);

    q->back = 0;
    q->front = 0;
    q->maxSize = numItems;
    
    return (void *)q;
}

// Adds an item to the back of the queue
void queue_enqueue(void *q, void *item) {
    
    Queue *myQueue = (Queue *)q;
    
    myQueue->array[myQueue->back] = item;
    myQueue->back = (myQueue->back + 1) % myQueue->maxSize;
    myQueue->size++;
}

// Removes an item from the front of the queue
void *queue_dequeue(void *q) {
    
    void *rv;

    Queue *myQueue = (Queue *)q;
    
    rv = myQueue->array[myQueue->front];
    
    myQueue->front = (myQueue->front + 1) % myQueue->maxSize;
    myQueue->size--;

    return rv;
}

// Checks if the queue is empty
int queue_isEmpty(void *q) {

    Queue *myQueue = (Queue *)q;

    if (myQueue->size == 0) {
        return 1;
    } else {
        return 0;
    }
}
