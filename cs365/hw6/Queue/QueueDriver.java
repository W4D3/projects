// QueueDriver.java
// Mitchell Wade
// Feb. 26, 2015

import java.util.*;

class QueueDriver {
    public static void main(String args[]) {
        
        Queue <String> myQueue;
        Scanner console = new Scanner(System.in);
        Scanner lineTokenizer;
        lineTokenizer = new Scanner(console.nextLine());
        myQueue = new Queue <String>(lineTokenizer.nextInt());
        lineTokenizer.close();

        while (console.hasNextLine()) {
            
            try {
                lineTokenizer = new Scanner(console.nextLine());
                String cmd = lineTokenizer.next();
                
                if (cmd.equals("enqueue")) {
                    myQueue.enqueue(lineTokenizer.next());
                } else if (cmd.equals("dequeue")) {
                    System.out.println(myQueue.dequeue());
                }
            }
            catch (QueueOverflowException q) {
                System.out.println(q.getMessage());
            }
            catch (QueueEmptyException q) {
                System.out.println(q.getMessage());
            }
            finally {
                lineTokenizer.close();
            }
        }
    }
}
