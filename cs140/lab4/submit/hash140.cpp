#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include "hash140.h"

using namespace std;

/*
   hash140.cpp
   Mitchell Wade
   February 27, 2014

   This program can add values to a hash table which in turn encrypts data.
   The program  allows the user to find values, print values in the hash 
   table, and also print the number of probes it took to put a certain value 
   into a hash table. Using XOR or Last7 the hash key is changed into a hash
   value which is then modded by the hash table size to get the hash location.
*/

// if you solve add, finding is the same thing put now you are looking for the
// key that is given instead of the empty spots
// you do find and count how many times you have to iterate, if the first one
// isn't one or two you do it again and add one
// if it takes one probe to do 20 keys, you return 20
// total probes you are repeating find and in find you are repeating hash?
// do the counting in add hash and you will have total probes
// if you can't find a place to put it in the table, do an error and quit
// ^----- you will have to call exit

/* Prototypes */
int XOR(string key);
int Last7(string key);

/* Hash Table Constructor */
HashTable::HashTable(int table_size, string function, string collision){

    /* Resize the hash table */
    keys.resize(table_size);
    vals.resize(table_size);

    /* Decides which hash function will be used */
    if (function == "XOR"){
        Fxn = 0;
    } else if (function == "Last7"){
        Fxn = 1;
    }

    /* Decides which collision strategy will be used */
    if (collision == "Linear"){
        Coll = 0;
    } else if (collision == "Double"){
        Coll = 1;
    }

    nkeys = 0;
    tmp = 0;
}

/* Adds a hash to a hash table */
void HashTable::Add_Hash(string &key, string &val){

    int i;                      /* Iteration variable */
    int value, value2;          /* The hash value */
    int location, location2;    /* The hash location */

    /* Print stderr if it is a hash table */
    if(nkeys == keys.size()){
        fprintf(stderr, "Hash Table Full\n");
        exit(1);
    }

    /* XOR */
    if (Fxn == 0){
       
        value = XOR(key) % keys.size();

        /* Linear */
        if (Coll == 0){
            i = 0;
            
            do {
                location = (value+i)%keys.size();
                i++;

                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        exit(1);
                    }
                }
            }while(keys[location] != "");
           
            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;

        /* Double */
        } else if (Coll == 1){

            value2 = Last7(key) % keys.size();
            if (value2 == 0)    value2 = 1;

            i = 0;
            do {
                location = (value+(value2*i) % keys.size())%keys.size();
                i++;
            
                /*
                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        return;
                    }
                }
                */

                if(i > keys.size()) {
                    cerr << "Couldn't put " << key << " into the table\n";
                    exit(1);
                }

            }while(keys[location] != "");

            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;
        }

    /* Last7 */
    } else if (Fxn == 1){
        
        value = Last7(key) % keys.size();

        /* Linear */
        if (Coll == 0){
         
            i = 0;
            do {
                location = (value+i)%keys.size();
                i++;

                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        exit(1);
                    }
                }
            }while(keys[location] != "");
            
            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;

        /* Double */
        } else if (Coll == 1){

            value2 = XOR(key) % keys.size();
            if (value2 == 0)    value2 = 1;

            /*
            //  FLAG
            for(i=0; i<keys.size(); i++) {
                location = (value+(value2*i)% keys.size())%keys.size();
                if(keys[location] == "") {
                    keys[location] = key;
                    vals[location] = val;
                    nkeys++;
                    return;
                }
            }
            cerr << "Couldn't put " << key << " into the table\n";
            exit(1);
            */
            i = 0;
            do {
                location = (value+(value2*i)% keys.size())%keys.size();
                i++;

                if(i > keys.size()) { 
                    cerr << "Couldn't put " << key << " into the table\n";
                    exit(1);
                }

                /*
                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        exit(1);
                    }
                }
                */
            }while(keys[location] != "");
                
            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;
        }
    }
}


/* Last7 hash function */
int Last7(string key){

    int value;   /* The hash value */
    string sub;  /* A substring */

    if (key.size() < 7){
        sscanf(key.c_str(), "%x", &value);
    } else { 
        sub = key.substr(key.size()-7, key.size()-1);
        sscanf(sub.c_str(), "%x", &value);
    }

    return value;
}

/* XOR hash function */
int XOR(string key){

    int i;               /* Iteration variables */
    int value = 0;           /* The hash value */
    int tempValue = 0;   /* The temperory hash value */
    int finalValue = 0;  /* The final hash value */
    string sub = "";     /* A substring */

    for (i=0; i<key.size(); i++){
            sub += key[i];
        if (i%7==6){
            //sscanf(sub.c_str(), "%x", &value);
            value = 0;
            stringstream ss(sub);
            ss >> hex >> value;
            finalValue = finalValue^value;
            //sub.clear();
            sub = "";
        }
    }
   
    /* Reads in the remaining characters in the string */
    //sscanf(sub.c_str(), "%x", &value);
    stringstream ss(sub);
    value = 0;
    ss >> hex >> value;
    finalValue = finalValue^value;
    //sub.clear();
    sub = "";

    return finalValue;
}

/* Finds a specific value within the hash table */
string HashTable::Find(string &key){

    int i;                      /* Iteration variable */
    int value, value2;          /* The hash value */
    int location, location2;    /* The hash location */

    
    /* Print stderr if it is a hash table */
    /*if(nkeys == keys.size()){
        fprintf(stderr, "Hash Table Full\n");
        exit(1);
    }
    */

    /* XOR */
    if (Fxn == 0){
       
        value = XOR(key) % keys.size();

        /* Linear */
        if (Coll == 0){
            i = 0;
            
            do {
                location = (value+i)%keys.size();
                i++;

                /*
                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        exit(1);
                    }
                }
                */
                if (i > keys.size()) return "";
            }while(keys[location] != key);

            return vals[location];

            /*
            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;
            */

        /* Double */
        } else if (Coll == 1){

            value2 = Last7(key) % keys.size();
            if (value2 == 0)    value2 = 1;

            i = 0;
            do {
                location = (value+(value2*i) % keys.size())%keys.size();
                i++;
            
                /*
                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        return;
                    }
                }
                */

                /*
                if(i > keys.size()) {
                    cerr << "Couldn't put " << key << " into the table\n";
                    exit(1);
                }
                */

                if (i > keys.size()) return "";
            }while(keys[location] != key);

            return vals[location];

            /*
            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;
            */
        
        }

    /* Last7 */
    } else if (Fxn == 1){
        
        value = Last7(key) % keys.size();

        /* Linear */
        if (Coll == 0){
         
            i = 0;
            do {
                location = (value+i)%keys.size();
                i++;

                /*
                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        exit(1);
                    }
                }
                */
                if (i > keys.size()) return "";
            }while(keys[location] != key);
            
            return vals[location];

            /*
            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;
            */

        /* Double */
        } else if (Coll == 1){

            value2 = XOR(key) % keys.size();
            if (value2 == 0)    value2 = 1;

            /*
            //  FLAG
            for(i=0; i<keys.size(); i++) {
                location = (value+(value2*i)% keys.size())%keys.size();
                if(keys[location] == "") {
                    keys[location] = key;
                    vals[location] = val;
                    nkeys++;
                    return;
                }
            }
            cerr << "Couldn't put " << key << " into the table\n";
            exit(1);
            */

            i = 0;
            do {
                location = (value+(value2*i)% keys.size())%keys.size();
                i++;

                /*
                if(i > keys.size()) { 
                    cerr << "Couldn't put " << key << " into the table\n";
                    exit(1);
                }
                */

                /*
                if(i==0){
                    location2 = location;
                } else if (i != 0){
                    if (location2 == location){
                        cerr << "Couldn't put " << key << " into the table\n";
                        exit(1);
                    }
                }
                */

                if (i > keys.size()) return "";
            }while(keys[location] != key);
              
            return vals[location];

            /*
            keys[location] = key;
            vals[location] = val;
            nkeys++;
            tmp += i-1;
            */
        }
    }
}

/* Prints out non-empty spots on the hash table */
void HashTable::Print(){

    int i;

    for (i=0; i<keys.size(); i++){
        if (keys[i] != ""){
            printf("%5d %s %s\n", i, keys[i].c_str(), vals[i].c_str());
        }
    }
}

/* Keeps track of the number of probes */
int HashTable::Total_Probes(){

    return tmp;

}
