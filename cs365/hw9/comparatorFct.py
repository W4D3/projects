# comparatorFct.py
# Mitchell Wade
# April 3, 2015
# This program compares two objects to determine
# where to place them on a binary tree in tree.py

def comparatorFct(key1, key2):
    if key1 < key2:
        return -1

    elif key1 == key2:
        return 0

    elif key1 > key2:
        return 1
