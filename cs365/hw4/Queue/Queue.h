// Queue.h
// Mitchell Wade
// Feb. 9, 2015

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>

using namespace std;

class Queue {

    public:
        virtual void add(int value) = 0;
        virtual int remove() = 0;
        virtual bool isEmpty() = 0;
};

class ArrayQueue : public Queue {
    
    list <int> Q;

    public:
        void add(int value);
        int remove();
        bool isEmpty();
};
