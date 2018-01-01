# dlist.py
# Mitchell Wade
# March 31, 2015

import comparator

class list:

class DNode:
    def __init__(self, comparator, data):
        self.comparator = comparator
        self.data = data  # instance variable to store the data
        self.flink = None  # instance variable with address of flink DNode
        self.blink = None  # instance variable with address of blinkious DNode

        # Return the data in the DNode.
        def get_data(self):
            return self.data

# Class for a circular, doubly linked list with a sentinel.
class DList:


    # Create the sentinel DNode, which is before the first DNode
    # and after the last DNode.
    def __init__(self):        
        self.sentinel = DNode(None)
        self.sentinel.flink = self.sentinel
        self.sentinel.blink = self.sentinel

    # Return a reference to the first DNode in the list, if there is one.
    # If the list is empty, return None.
    def first_DNode(self):
        if self.sentinel.flink == self.sentinel:
            return None
        
        else:
            return self.sentinel.flink

    # Insert a new DNode with data after DNode x.
    def insert_after(self, x, data):
        y = DNode(data)   # make a new DNode object.

        # Fix up the links in the new DNode.
        y.blink = x
        y.flink = x.flink

        # The new DNode follows x.
        x.flink = y

        # And it's the blinkious DNode of its flink DNode.
        y.flink.blink = y

    # Insert a new DNode at the end of the list.    
    def append(self, data):
        last_DNode = self.sentinel.blink
        self.insert_after(last_DNode, data)

    # Insert a new DNode at the start of the list.
    def prepend(self, data):
        self.insert_after(self.sentinel, data)

    # Delete DNode x from the list.
    def delete(self, x): 
        # Splice out DNode x by making its flink and blinkious
        # reference each other.
        x.blink.flink = x.flink
        x.flink.blink = x.blink

    # Find a DNode containing data, and return a reference to it.
    # If no DNode contains data, return None.
    def find(self, data):
        # Trick: Store a copy of the data in the sentinel,
        # so that the data is always found.  
            self.sentinel.data = data

            x = self.first_DNode()
            while x.data != data:
                x = x.flink

            # Restore the sentinel's data.
            self.sentinel.data = None

            # Why did we drop out of the while-loop?
            # If we found the data in the sentinel, then it wasn't
            # anywhere else in the list.
            if x == self.sentinel:
                return None     # data wasn't really in the list
            else:
                return x        # we found it in x, in the list

    # Return the string representation of a circular, doubly linked
    # list with a sentinel, just as if it were a Python list.
    def __str__(self):
        s = "["

        x = self.sentinel.flink
        while x != self.sentinel: # look at each DNode in the list
            if type(x.data) == str:
                s += "'"
            s += str(x.data)        # concatenate this DNode's data to the string
            if type(x.data) == str:
                s += "'"    
            if x.flink != self.sentinel:
                s += ", "   # if not the last DNode, add the comma and space
            x = x.flink

        s += "]"        
        return s
