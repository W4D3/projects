# tree.py
# Mitchell Wade
# April 3, 2015
# This program is the API for a BST.

import comparatorFct

class BinaryTree:

    # Constructs an empty BinaryTree
    def __init__(self, comparatorFct):
        self.compare = comparatorFct
        self.size = 0
        self.sentinel = Node()
        self.sentinel.right = self.sentinel

    # Inserts a new key onto the tree
    def insert(self, key):
        parent = self.sentinel
        n = self.sentinel.right

        # Look for key and if already on the tree
        # dont add it and return
        while n != self.sentinel:
            if n.key == key:
                return
            
            parent = n
            
            if self.compare(key, n.key) == -1:
                n = n.left
            else:
                n = n.right

        # Create a new Node and update its links
        n = Node()
        n.key = key
        n.parent = parent
        n.left = self.sentinel
        n.right = self.sentinel

        if parent == self.sentinel:
            self.sentinel.right = n
        elif self.compare(key, parent.key) == -1:
            parent.left = n
        else:
            parent.right = n

        # Update the size of the tree
        self.size = self.size + 1

    # Returns true if the key is in the tree and
    # false otherwise
    def find(self, key):
        n = self.sentinel.right

        while 1:
            if n == self.sentinel:
                return False

            result = self.compare(key, n.key)
            if result == 0:
                return True
            elif result == -1:
                n = n.left
            else:
                n = n.right

    # Traverses the tree in a in order search
    def traverse(self):
        return self.inOrder(self.sentinel.right)

    def inOrder(self, node):
        if node == self.sentinel:
            return

        # prints out the tree
        for data in self.inOrder(node.left):
            yield data
        yield node.key
        for data in self.inOrder(node.right):
            yield data

class Node:
    def __init__(self):
        self.parent = None
        self.left = None
        self.right = None
        key = None
