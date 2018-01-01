# Inserts the value after the node# dlist.py
# Mitchell Wade
# March 31, 2015

import comparator

class DNode:
    def __init__(self, comparator, node):
        self.comparator = comparator
        self.node = node
        self.flink = None
        self.blink = None

class DList:

    # Create a sentinel node
    def __init__(self):        
        self.sentinel = DNode(None)
        self.sentinel.flink = self.sentinel
        self.sentinel.blink = self.sentinel

    # Inserts the value after the node
    def insertAfter(self, value, node):
        
        # Make a new node
        y = DNode(node)
        
        # Change links in new node
        y.blink = value
        y.flink = value.flink
        
        # Fix old flink
        value.flink = y
        
        # Set the new nodes flink
        y.flink.blink = y

    # Inserts the value before the node
    def insertBefore(self, value, node):

        # Make a new node
        y = DNode(node)

        # Change links in new node
        y.flink = value
        y.blink = value.blink

        # Fix old blink
        value.blink = y

        # Set the new nodes blink
        y.blink.flink = y

    # Appends the value to the list
    def append(self, value):
        last_DNode = self.sentinel.blink
        self.insertAfter(last_DNode, value)

    # Removes the specified node from the list
    def erase(self, node): 
        node.blink.flink = node.flink
        node.flink.blink = node.blink

    # A generator function that returns the next node in the list
    def __iter__(self):
        return iter(self.flink)     

    # Returns the first node that contains the value or none
    def find(self, value):
    
        self.sentinel.node = value

        node = self.firstDNode()
        while node.value != value:
            node = node.flink

            # Restore the sentinel's node.
            self.sentinel.value = None

            # Check to see if it was or wasn't on the list
            if node == self.sentinel:
                return None     # node wasn't on the list
            else:
                return node        # node was on the list
