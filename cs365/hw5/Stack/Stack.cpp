// Stack.cpp
// Mitchell Wade
// Feb. 17, 2015
// This program is implementation for a stack in C++.

// CONSTRUCTOR
template <class E, int MAX_SIZE>
Stack<E, MAX_SIZE>::Stack(int maxSize): maxCap(maxSize) {}

// PUSH
template <class E, int MAX_SIZE>
bool Stack<E, MAX_SIZE>::push(E value) {
    
    if (data.size() == maxCap)
        return false;
    else {
        data.push_back(value);
        return true;
    }
}

// POP
template <class E, int MAX_SIZE>
E Stack<E, MAX_SIZE>::pop() {
    
    E value = data.back();
    data.pop_back();
    
    return value;
}

// ISEMPTY
template <class E, int MAX_SIZE>
bool Stack<E, MAX_SIZE>::isEmpty() {
    
    return data.empty();
}
