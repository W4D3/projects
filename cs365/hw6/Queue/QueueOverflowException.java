// QueueOverflowException.java
// Mitchell Wade
// Feb. 26, 2015

package queue;

public class QueueOverflowException extends Exception {
    
    Object valueToEnqueue;
    QueueOverflowException(Object value) {
        valueToEnqueue = value;
    }
    public String getMessage() {
        return "queue full: cannot enqueue " + valueToEnqueue;
    }
}
