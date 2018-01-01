// QueueDriver.cpp
// Mitchell Wade
// Feb. 9, 2015

#include "Queue.h"

#include <iostream>

using namespace std;

int main() {

    Queue *q = new ArrayQueue();

    // Add some values to the queue
    q->add(3);
    q->add(10);
    q->add(5);
    
    // Pop two values off and print
    printf("%d\n", q->remove());
    printf("%d\n", q->remove());

    // Add some more values
    q->add(6);
    q->add(9);
    q->add(12);

    // Pop and print till empty
    while (!q->isEmpty()) printf("%d\n", q->remove());
}
