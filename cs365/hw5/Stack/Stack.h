// Stack.h
// Mitchell Wade
// Feb. 17, 2015
// This program is the header for a stack implementation in C++.

#include <iostream>
#include <vector>

using namespace std;

template <class E, int MAX_SIZE = 100>
class Stack {
    protected:
        vector <E> data;
        int maxCap;

    public:

        /*
        Stack() {
            maxCap = MAX_SIZE;
            //...
        }
        */

        Stack(int maxSize = MAX_SIZE);
        bool push(E value);
        E pop();
        bool isEmpty();
};

#include "Stack.cpp"
