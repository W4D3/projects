// queue.h
// Mitchell Wade
// Feb. 17, 2015
// This program is the header for a queue implementation in C.

void *queue_new(int numItems);
void queue_enqueue(void *q, void *item);
void *queue_dequeue(void *q);
int queue_isEmpty(void *q);
