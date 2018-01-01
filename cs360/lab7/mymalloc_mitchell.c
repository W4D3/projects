// mymalloc.c
// Mitchell Wade
// March 25, 2015
// This program resembles the system call malloc(). It
// allocated memory from the heap and when memory is done
// being used it is stored on a free list until the 
// termination of the program.

#include <stdlib.h>
#include <stdio.h>

// Free list structure
typedef struct flist {
    int size;
    struct flist *flink;
    struct flist *blink;
} *Flist;

Flist head = NULL;

// Returns a ptr to the first node on the free list
void *free_list_begin() {

    return head;
}

// Returns the first free node on the free list
void *free_list_next(void *node) {

    Flist fl;

    fl = node;

    return fl->flink;
}

// Coalesces the memory on the free list
void *coalesce_free_list() {

    // make an array of ints that holds the address of the node

    // comparator fnx = subtract the two addresses together
    // subtract the big number from the small number
    //qsort(...)

    // change sizes if they are next to eachother
    // otherwise set the next flink to the next node
}

void my_free(void *ptr) {
    
    // backup 8

    // set all things back to null

    // link flinks and blinks back up to the free nodes around it
}

void *my_malloc(size_t size) {

    int rem = 0, div = 0, i, starting_point = 0, ending_point = 0;
    int *ptr;
    Flist f;

    // No free list exists
    if (head == NULL) {

        // Check if it is under 8192 or above it
        if (size < 8176) {

            // Make sure its divisible by 8 and add bookkeeping
            if (size%8 != 0) {
                rem = size%8;
                div = 8-rem;
                size = size+div+8;
                printf("size: %d\n", size);
            } else {
                size = size+8;
                printf("size: %d\n", size);
            }
            
            i = sbrk(8192);

            // Make a new free list node
            head = (Flist)i;
            head->flink = NULL;
            head->blink = NULL;
            head->size = 8192;

            // Carve off specified memory from the bottom of the free list
            ending_point = (int)head + 8192;
            starting_point = ending_point - (int)size;
            ptr = (int*)starting_point;
            f = (Flist)ptr;

            // Fill in the allocated memory's size
            f->size = size;
            //printf("f->size: %d\n", f->size);

            // Fill in the flink
            f->flink = (Flist)ptr;

            // Fill in the blink
            f->blink = NULL;

            // Return the specified memory starting address
            return (void *)ptr + 8;

        } else {

            // Make sure its divisible by 8 and add bookkeeping
            if (size%8 != 0) {
                rem = size%8;
                div = 8-rem;
                size = size+div+8;
            } else {
                size = size+8;
            }
            
            i = sbrk(size);
            
            // Make a new free list node
            head = (Flist)i;
            head->blink = NULL;
            head->flink = NULL;
            head->size = size;

            // Carve off specified memory from the bottom of the free list
            ending_point = (int)head + size + 8;
            starting_point = ending_point - (int)size;
            ptr = (int*)starting_point;
            f = (Flist)ptr;
            
            // Fill in the allocated memory's size
            f->size = size;
            //printf("f->size: %d\n", f->size);

            // Fill in the flink
            f->flink = (Flist)ptr;

            // Fill in the blink
            f->blink = NULL;

            // Return the specified memory starting address
            return (void *)ptr + 8;
        }

        // A free list exists
    } else {

        // check if a node exists that is big enough

        // chase flink pts
            // if not null
            // if size is bigger than asked for
                // use this node
                // use this node and split it up


        /*
        // Make a new free list node
        head = i;
        head->flink = NULL;
        head->blink = NULL;
        head->size = size;
         */        
    }
}


// carve off the free list
    // head - size

// gradescript 41+ == coalesce free list stuff

