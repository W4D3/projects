// Stack.java
// Mitchell Wade
// Feb. 17, 2015
// This program is implementation for a stack in Java.

package Stack;

import java.util.*;

public class Stack <T>{

    Vector <T> v = new Vector <T>();
    private int MaxCap = 0;
    private final static int MAX_SIZE = 100;
    private T value;

    // DEFAULT CONSTUCTOR
    public Stack() {
        MaxCap = MAX_SIZE;
    }

    // SPECIFIED CONSTRUCTOR
    public Stack(int maxSize) {
        MaxCap = maxSize;
    }

    // PUSH
    public boolean push(T value) {
        
        if (v.size() == MaxCap) {
            return false;
        } else {
            v.add(value);
            return true;
        }
    }

    // POP
    public T pop() {

        value = v.remove(0);
        return value;

    }

    // ISEMPTY
    public boolean isEmpty() {
        return v.isEmpty();
    }
}
