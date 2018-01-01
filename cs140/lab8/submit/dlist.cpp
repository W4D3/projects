#include <iostream>
#include <cstdlib>
#include "dlist.h"
using namespace std;

/*
   dlist.cpp
   Mitchell Wade
   April 15, 2014
*/

/* Constructor for a new dlist (sentinel) */
Dlist::Dlist() {

    sentinel = new Dnode;
    sentinel->flink = sentinel;
    sentinel->blink = sentinel;
    size = 0;

}

/* Deconstructor to delete the list*/
Dlist::~Dlist() {

    Dnode *tmp;     /* Temporary node */

    /* While there are nodes remaining... */
    while (size != 0) {

        /* Grab the next node */
        tmp = sentinel->flink;

        /* Set the sentinels flink to the 2nd node in the list */
        sentinel->flink = sentinel->flink->flink;

        /* Delete the first node */
        delete tmp;
        
        /* Decrement the size of the list */
        size--;
    }

    delete sentinel;
}

/* Outputs if the list is empty or not */
int Dlist::Empty() {

    if (size == 0) {
        return 1;       //true = empty
    } else 
        return 0;       //false = not empty
}

/* Returns the size of Dlist */
int Dlist::Size() {
    
    return size;

}

/* Adds a new node in front of the Dlist sentinel */
void Dlist::Push_Front(string s) {
    
    Dnode *newNode;     /* Ptr for new node */
    Dnode *prev;        /* Previous node */
    Dnode *next;        /* Next node */

    /* Create the new node */
    newNode = new Dnode;

    /* Initalize handles */
    prev = sentinel;
    next = sentinel->flink;

    /* Initalize the new nodes string value */
    newNode->s = s;

    /* Change links */
    newNode->flink = next;
    newNode->blink = prev;
    next->blink = newNode;
    prev->flink = newNode;

    /* Increment the size of the list */
    size++;
}

/* Adds a new node in front of the Dlist sentinel */
void Dlist::Push_Back(string s) {

    Dnode *newNode;     /* Ptr for new node */
    Dnode *prev;        /* Previous node */
    Dnode *next;        /* Next node */

    /* Create the new node */
    newNode = new Dnode;

    /* Initalize handles */
    prev = sentinel->blink;
    next = sentinel;

    /* Initalize the new nodes string value */
    newNode->s = s;

    /* Change links */
    newNode->flink = next;
    newNode->blink = prev;
    next->blink = newNode;
    prev->flink = newNode;

    /* Increment the size of the list */
    size++;
}

string Dlist::Pop_Front() {

    Dnode *prev;        /* Previous node */
    Dnode *next;        /* Next node */
    string tmp;         /* Temporary string for deleted node */

    /* Initalize handles */
    next = sentinel->flink->flink;
    prev = sentinel;

    /* Save the string of the deleted node */
    tmp = sentinel->flink->s;

    /* Delete the first node */
    delete sentinel->flink;
    
    /* Change links */
    next->blink = sentinel;
    prev->flink = next;

    /* Decrement the size of list */
    size--;

    /* Return the string of the deleted node */
    return tmp;
}

string Dlist::Pop_Back() {

    Dnode *prev;        /* Previous node */
    Dnode *next;        /* Next node */
    string tmp;         /* Temporary string for deleted node */
    
    /* Initalize handles */
    next = sentinel->blink->blink;
    prev = sentinel;
    
    /* Save the string of the deleted node */
    tmp = sentinel->blink->s;

    /* Delete the last node */
    delete sentinel->blink;
    
    /* Change links */
    next->flink = sentinel;
    prev->blink = next;
    
    /* Decrement the size of list */
    size--;

    /* Return the string of the deleted node */
    return tmp;
}

/* Return the beginning node of the list */
Dnode* Dlist::Begin() {

    return sentinel->flink;

}

/* Return the ending node of the list */
Dnode* Dlist::End() {

    return sentinel;

}

/* Return the reverse beginning node of the list */
Dnode* Dlist::Rbegin() {

    return sentinel->blink;

}

/* Return the reverse ending node of the list */
Dnode* Dlist::Rend() {

    return sentinel;

}

/* Insert a new node before the node n */
void Dlist::Insert_Before(string s, Dnode *n) {

    Dnode *newNode;     /* Ptr for new node */
    Dnode *prev;        /* Previous node */
    Dnode *next;        /* Next node */

    /* Create the new node */
    newNode = new Dnode;
    
    /* Initalize the new nodes string value */
    newNode->s = s;

    /* Initalize handles */
    prev = n->blink;
    next = n;

    /* Change the links */
    newNode->flink = next;
    newNode-> blink = prev;
    n->blink->flink = newNode;
    n->blink = newNode;

    /* Increment the size of the list */
    size++;
}

/* Insert a new node after the node n */
void Dlist::Insert_After(string s, Dnode *n) {

    Dnode *newNode;     /* Ptr for new node */
    Dnode *prev;        /* Previous node */
    Dnode *next;        /* Next node */

    /* Create the new node */
    newNode = new Dnode;
    
    /* Initalize the new nodes string value */
    newNode->s = s;

    /* Initalize handles */
    prev = n;
    next = n->flink;

    /* Change the links */
    newNode->blink = prev;
    newNode->flink = next;
    n->flink->blink = newNode;
    n->flink = newNode;

    /* Increment the size of the list */
    size++;
}

/* Delete the node n */
void Dlist::Erase(Dnode *n) {

    Dnode *prev;        /* Previous node */
    Dnode *next;        /* Next node */

    /* Initalize handles */
    next = n->flink;
    prev = n->blink;

    /* Change the links */
    next->blink = prev;
    prev->flink = next;

    /* Delete node */
    delete n;

    /* Decrement the size of list */
    size--;
}
