// Queue.java
// Mitchell Wade
// Feb. 26, 2015

package queue;

import java.util.Vector;

public class Queue <E> {

    Vector <E> items;
    int next_free;
    int next_full;
    int max_items;
    int size;

    public Queue(int maxItems) {
        items = new Vector <E>(maxItems);
        items.setSize(maxItems);
        next_free = 0;
        next_full = 0;
        max_items = maxItems;
        size = 0;
    }

    public void enqueue(E item) throws QueueOverflowException {
        if (size == max_items) {
            throw new QueueOverflowException(item);
        }

        items.set(next_free, item);
        next_free = (next_free + 1) % max_items;
        size++;
    }

    public E dequeue() throws QueueEmptyException {
        if (size == 0) {
            throw new QueueEmptyException();
        }
        
        E returnValue = items.get(next_full);
        next_full = (next_full + 1) % max_items;
        size--;
        return returnValue;
    }
}
