#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "cs302-midi.h"
using namespace std;

// cs302-midi.cpp
// Mitchell Wade
// Sep. 21, 2014
// This program converts a midi note file to a midi event file
// and vice versa. There are two functions and each function
// converts between note and event files by usings maps, ptrs,
// and basic structures from the std library.

void CS302_Midi::el_to_nd()
{
    int i = 0;
    double time = 0;
    ND *n;
    vector <ND *> notes;
    list <Event *>::iterator lit;                        

    // Creates the ND map from the typedef multimap <double, ND *> NDMap;
    nd = new NDMap;

    // Make the vector the correct size for the events
    notes.resize(129, NULL);

    time = 0;
    for(lit = el->begin(); lit != el->end(); lit++){
        
        // After each iteration of the el list add up the time of events
        time += ((*lit)->time / 480.0);

        // Create the ON Events
        if((*lit)->key == 'O'){
            n = new ND;
            n->key = 'N';
            n->pitch = (*lit)->v1;
            n->volume = (*lit)->v2;
            n->start = time;

            // Add the Event to the vector
            notes[n->pitch] = n;
        }

        // Create the OFF Events
        if((*lit)->key == 'F'){
            if(notes[(*lit)->v1] != NULL){
                n = notes[(*lit)->v1];
                notes[(*lit)->v1] = NULL;
                n->stop = time;
                
                // Add the Event to the vector
                nd->insert(make_pair(n->start, n));
            }
        }

        // Create the DOWN Events
        if((*lit)->key == 'D'){
            if((*lit)->v1 == 1){
                n = new ND;
                n->key = 'D';
                n->start = time;

                // Add the Event to the vector
                notes[128] = n;
            }
            
            // Create the UP Events
            if((*lit)->v1 == 0){
                if(notes[128] != NULL){
                    n = notes[128];
                    notes[128] = NULL;
                    n->stop = time;

                    // Add the Event to the vector
                    nd->insert(make_pair(n->start, n));
                }
            }
        }
    }

    // Complete filling out the Events
    for(i = 0; i < notes.size(); i++){
        if(notes[i] != NULL){
            n = notes[i];
            notes[i] = NULL;
            n->stop = time;
            
            // Add the Event to the map
            nd->insert(make_pair(n->start, n));
        }
    }
}

void CS302_Midi::nd_to_el()
{
    multimap <double, ND *>::iterator ndit; // Iterator to traverse the map of ND events
    Event *eON;     // eON and eDOWN pointers
    Event *eOFF;    // eOFF and eUP pointers
    ND *n;          // Note/Damper event pointer
    map <int, multimap <int, Event *> > tmp; // A temporary map to sequence all of the events correctly
    map <int, multimap <int, Event *> >:: iterator tmpit; // tmp map pointer
    multimap <int, Event *>:: iterator tmpit1; // Pointer for the multimap of event instances inside the tmp map 
    int eTYPE = 0, eTYPE1 = 0; // Temporary integers to sequence the events correctly

    // Creates a new event list from the typdedef list <Event i*> EventList;
    el = new EventList;

    // Create all events as instances of the Event class from the note damper map
    for (ndit = nd->begin(); ndit !=  nd->end(); ndit++) {

        // Grab the first instance of an nd
        n = ndit->second;

        // Create the Note Events
        if (n->key == 'N') {

            //On Event
            eON = new Event;
            eON->key = 'O';
            eON->v1 = n->pitch;
            eON->v2 = n->volume;
            eON->time = rint(n->start * 480);
            eTYPE = 3;

            //Off Event
            eOFF = new Event;
            eOFF->key = 'F';
            eOFF->v1 = n->pitch;
            eOFF->time = rint(n->stop * 480);
            eTYPE1 = 0;
        }

        // Create the Damper Events
        if (n->key == 'D') {

            // Down Event
            eON = new Event;
            eON->key = 'D';
            eON->v1 = 1;
            eON->v2 = 0;
            eON->time = rint(n->start * 480);
            eTYPE = 2;

            // UP Event
            eOFF = new Event;
            eOFF->key = 'D';
            eOFF->v1 = 0;
            eOFF->v2 = 0;
            eOFF->time = rint(n->stop * 480);
            eTYPE1 = 1;
        }

        // Add the events to the temporary map in the correct order
        // Order: OFF, DAMPER UP, DAMPER DOWN, ON
        if(eON->time != eOFF->time) {
            tmp[eON->time].insert(make_pair(eTYPE, eON));
            tmp[eOFF->time].insert(make_pair(eTYPE1, eOFF));
        }
    }

    int time = 0;

    // Pushback the elements of the tmp map to the el list
    for (tmpit = tmp.begin(); tmpit != tmp.end(); tmpit++) {
        for (tmpit1 = tmpit->second.begin(); tmpit1 != tmpit->second.end(); tmpit1++) {

            if(tmpit1 == tmpit->second.begin()) {
                tmpit1->second->time = tmpit->first - time;
            } else {
                tmpit1->second->time = 0; 
            }

            el->push_back(tmpit1->second);
        }

        time = tmpit->first;
    }
}
