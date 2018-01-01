#include <iostream>
#include <iomanip>
#include <string.h>
#include "dl_hash.h"

using namespace std;

/* DJB Hash Function */
unsigned int djb_hash(string &s) {
    
    int i;
    unsigned int h;
    
    h = 5381;
    
    for (i = 0; i < s.size(); i++) {
        h = (h << 5) + h + s[i];
    }
    
    return h;
}

/* Hash Table Constructor */
DL_Hash::DL_Hash(int size) {

    int i;

    table.resize(size);

    for (i=0; i<size; i++) {
        table[i] = new Dlist;
    }
}

/* Hash Table Destructor */
DL_Hash::~DL_Hash() {
    
    int i;

    for (i=0; i < table.size(); i++) {
        delete table[i];
    }
}

void DL_Hash::Insert(string &s) {

    unsigned int location;
    int i;
    int j = 0;
    Dlist *ptr;

    /* Hash the location using the string */
    location = djb_hash(s)%table.size();

    /* Initalize the link  */
    ptr = table[location];

    /* Add the string to the hash table  */
    if (Present(s) == 0) ptr->Push_Back(s);

}

int DL_Hash::Present(string &s) {

    int flag = 0;
    unsigned int location;
    Dlist *ptr;
    Dnode *node;

    /* Hash the location using the string */
    location = djb_hash(s)%table.size();
    
    /* Initalize the link  */
    ptr = table[location];

    /* Check to see if the string is in the hash table */
    for (node = ptr->Begin(); node != ptr->End(); node = node->flink) {
        if (node->s == s) {
            flag = 1; //set to 1 if found
            break;
        }
    }

    return flag;
}

void DL_Hash::Erase(string &s) {

    int flag;
    unsigned int location;
    Dnode *node;
    Dlist *ptr;

    /* Hash the location using the string */
    location = djb_hash(s)%table.size();
    
    /* Initalize the link  */
    ptr = table[location];

    /* Check to see if the string is in the hash table */
    for (node = ptr->Begin(); node != ptr->End(); node = node->flink) {
        if (node->s == s) {
            ptr->Erase(node);
            break;
        }
    }
}

/* Delete a specific string from the hash table */
void DL_Hash::Strip_All_Substring(string &s) {

    int i, j, k;
    string tmp;
    Dnode *node;
    Dlist *ptr;

    /* Read the through the entire hash table */
    for (i=0; i<table.size(); i++) {

        ptr = table[i]; //set a pointer to each location

        /* Delete each substring in the hash table  */
        for (node = ptr->Begin(); node != ptr->End(); node = node->flink) {
            if (strstr((node)->s.c_str(), s.c_str()) != NULL) {
                ptr->Erase(node);
            }
        }
    }
}

/* Prints the hash table to standard output */
void DL_Hash::Print() {

    int i;
    Dlist *ptr;
    Dnode *node;

    /* Read the through the entire hash table */
    for (i = 0; i < table.size(); i++) {
        
        ptr = table[i]; //set a pointer to each location
        
        /* Read through each Dlist in the vector called table*/
        for (node = ptr->Begin(); node != ptr->End(); node = node->flink) {
            cout << setw(4) << i << " " << node->s << endl;
        }
    }
}

