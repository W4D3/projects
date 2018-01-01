// ArrayQueue.cpp
// Mitchell Wade
// Feb. 9, 2015

#include "Queue.h"
#include <list>

using namespace std;

// Add a value to the queue
void ArrayQueue::add(int value) {
    
    Q.push_back(value);
}

// Remove a value off the queue
int ArrayQueue::remove() {
    
    int rv;    
    
    rv = Q.front();
    Q.pop_front();

    return rv;
}

// Return if it is empty or not
bool ArrayQueue::isEmpty() {
    
    return Q.empty();
}

