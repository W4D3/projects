// ArrayQueue.java
// Mitchell Wade
// Feb. 3, 2015
//
// This program implements the Queue.java interface.

import java.util.ArrayList;

class ArrayQueue implements Queue {
    
    ArrayList<Object> list = new ArrayList<Object>();
    
    public void add(Object o) {
        list.add(o);
    }
    public Object remove() {
        return list.remove(0);
    }
    public boolean isEmpty() {
        return list.isEmpty();
    }
}
