// LinkedList.java
// Mitchell Wade
// Feb. 9, 2015

package Graphics;

import java.util.*;

package LinkedList;

class ListNode {
    protected int value;
    String name;
}

package LinkedList;

public class List {
    ListNode header;
    protected ListNode sentinelNode;

    public List() {
        header = new ListNode();
            header.value = 10;
            header.name = "brad";
        sentinelNode = new ListNode();
    }
}

package LinkedQueue;

class Queue extends LinkedList.List {
    public Queue() {
            header.value = 20;
            sentinelNode.value = 30;
    }
}
