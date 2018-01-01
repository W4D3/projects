// QueueEmptyException.java
// Mitchell Wade
// Feb. 26, 2015

package queue;

public class QueueEmptyException extends Exception {
    public String getMessage() {
        return "queue empty: cannot dequeue ";
    }
}
