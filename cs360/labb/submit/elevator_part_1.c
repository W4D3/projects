// elevator_part_1.c
// Mitchell Wade
// April 21, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "elevator.h"
#include "dllist.h"

typedef struct data {
    Dllist people;
    pthread_cond_t *cv;
} Data;

Data *d;

//Set up the global list and a condition variable for blocking elevators.
void initialize_simulation(Elevator_Simulation *es)
{
    d = (Data *) malloc(sizeof(Data));
    d->people = new_dllist();
    d->cv = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));

    // Store the global list in the Elevator Simulation struct
    es->v = d;
}

void initialize_elevator(Elevator *e)
{

}

void initialize_person(Person *e)
{

}

void wait_for_elevator(Person *p)
{

    // could look for new people in line of taking the next person

    // Append the person to the global list.
    dll_append(d->people, new_jval_v((void *) p));

    // Signal the condition variable for blocking elevators.
    pthread_cond_signal(d->cv);

    // Block on the person's condition variable.
    pthread_cond_wait(p->cond, p->lock);
}

void wait_to_get_off_elevator(Person *p)
{
    // Unblock the elevator's condition variable
    pthread_cond_signal(p->e->cond);

    // Block on the person's condition variable. 
    pthread_cond_wait(p->cond, p->lock);
}

void person_done(Person *p)
{
    // Unblock the elevator's condition variable
    pthread_cond_signal(p->e->cond);
}

void *elevator(void *arg)
{
    Person *p;
    Elevator *e;
    e = (Elevator *) arg;
    Dllist tmp;

    while (1) {

        // If the global list is empty,
        if (dll_empty(d->people)) {
            
            // block on the condition variable for blocking elevators. 
            pthread_cond_wait(d->cv, e->lock);
        
        }

        // Grab the first person off the queue of waiting for an elevator
        tmp = (Dllist *) dll_first(d->people);
        p = (Person *) tmp->val.v;

        // Remove the person from the list
        dll_delete_node(tmp);

        // When the elevator gets a person to service
        // it moves to the appropriate floor and opens its door. 
        //pthread_mutex_unlock(e->lock);
        move_to_floor(e, p->from);
        open_door(e);

        // It puts itself into the person's e field, 
        p->e = e; 
        
        // Then signals the person and blocks until the person wakes it up 
        pthread_cond_signal(p->cond);
        pthread_cond_wait(e->cond, e->lock);
        pthread_mutex_unlock(e->lock);
        close_door(e);

        // When it wakes up, it goes to the person's destination floor... 
        move_to_floor(e, p->to);

        // Opens its door, signals the person and blocks.
        open_door(e);
        pthread_cond_signal(p->cond);
        pthread_cond_wait(e->cond, e->lock);

        // When the person wakes it up, 
        // it closes its door and re-executes its while loop. 
        pthread_mutex_unlock(e->lock);
        close_door(e);
    }

    return NULL;
}
