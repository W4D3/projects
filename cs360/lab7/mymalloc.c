// mymalloc.c
// Mitchell Wade
// March 25, 2015
// This program resembles the system call malloc(). It
// allocated memory from the heap and when memory is done
// being used it is stored on a free list until the
// termination of the program.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *head;

struct Node{
	size_t size;
	struct Node *blink;
	struct Node *flink;
};

void *my_malloc(size_t size){
	
    // Check if it is a multiple of 8
    if (size%8 != 0) {
        size += 8 - (size % 8);
    }

    // Add bookkeeping
    size += 8;

    if (head == NULL) {

		intptr_t num = size > 8192 ? size : 8192;
        head = sbrk(num);
        void *ret = head;

        // Check current size
		if (size+4 <= num) {

			// Make a freelist
            head += size;
			struct Node *n = head;
			n->size = num - size;
			n->blink = NULL;
			n->flink = NULL;
		
        } else {
			head = NULL;	
		}

		int *i = ret;
		*i = size;
		return (void *)((int)ret+8);
	}

	struct	Node *n = head;
	int test = -1;
	
    // Check for a node that can be allocated for the user
    while (1){
		
        if (n->size >= size + 4){
			test = 0;
			break;
		}
		if (n->size >= size){
            test = 1;
			break;
		}

		if (n->flink == NULL) {
            test = 2;
			break;
		}
		n = n->flink;
	}

    // Create a freelist node and return it to the user
	if (test == 0){
		
        struct Node *f = (void*)((int)n + size);
		
        f->size = n->size -size;
		f->flink = n->flink;
		f->blink = n->blink;
		
        if (n->flink != NULL) n->flink->blink = f;
		if (n->blink != NULL) n->blink->flink = f;
		
        n->size = size;
		
        if (n == head)head = f;	

		return (void*)((int)n+8);
	}

    // Delete a node from the freelist and return it to the user
	if (test == 1) {
		
        if (n->flink != NULL) n->flink->blink = n->blink;
		if (n->blink != NULL) n->blink->flink = n->flink;
		
        n->size = size;
		
        if (head == n){
			if (n->flink != NULL) n->flink->blink = NULL;
			
            head = n->flink;
		}

		return (void*)(int)n+8;
	}

	// Create more memory if needed
    intptr_t num = size > 8192 ? size : 8192;
	void *ret = sbrk(num);
	
    if (size+4 <= num){

		struct Node * f =(void *)( ((int)ret) + size);
		
        f->size = num - size;
		f->blink = n;
		f->flink = NULL;
		
        n->flink = f;
	}
	
    int *i = ret;
	*i = size;
	
    return (void *)(int)ret+8;

}

// Add nodes back onto the free list
void my_free(void *ptr){
	
    struct	Node *n;
	
    if (head != NULL){ 
		n = head;
		
        // Grab the next free node
        while (n->flink != NULL){
			n = n->flink;
		}

		struct Node *f = (void*)(int)ptr-8;

		n->flink = f;
		f->blink = n;
		f->flink = NULL;

	} else {
		
        // Add a new node to the freelist if it is empty
        struct Node * f = ptr-8;
		f->flink = f->blink = NULL;
		head = f;
	}
}

// Return the next free node
void *free_list_begin() {

	return head;
}

// Returns the next node after the specified node
void *free_list_next(void *node) {
	
    struct Node * n = node;
	
    return n->flink;
}

// Comparator function for quicksort
int comparator(void * a, void * b) {

    int *node1 = (int *)a;
	int *node2 = (int *)b;
	
    return *node1  - *node2; 
}

// Add all nodes on the freelist to one freelist
void coalesce_free_list(){
	
    int i = 0, j = 0, k = 0, c = 0;

	struct Node *n = head;

	if (head != NULL) {

        // Count the number of nodes
		while (n != NULL){
			n = n->flink;
			++i;
		}

		// Make an array and assign the pointers to the array
		int l[i];
		n = head;

		for (j = 0; j < i; j++){
			
            l[j] =(int) n;
			n = n->flink;
		}

		// Sorts the array
		qsort(l, i, sizeof(int), (__compar_fn_t)comparator);
		n = head;
		
        while (1){
			
            c = 0;
			
            for (j = 0; j < i-1; j++){
				
                struct Node * a = (struct Node*)l[j];
				
                for (k = j+1; k < i; k++){
					
					// Find the next node that is larger
                    if (l[j] > 0 && l[k] > 0 && l[j] + a->size == l[k]) {
						
						c++;

                        //If it is adj, add the sizes to the lowest adjacent node, and remove the nodes
						struct Node * b = (struct Node*)l[k];
						a->size += b->size;
						b->size = 0;
						l[k] = -1;
					}
				}
			}

			if (c == 0) break;
		}

		//Reset the freelist
		struct Node *m;
		head = (void *) l[0];
		m = head;
		m->flink = m->blink = NULL;
		
        for (c = 1; c < i; c++){

			if (l[c] != -1){
				n = (void *)l[c];
				m->flink = n;
				n->blink = m;
				m = n;
			}
		}
		m->flink = NULL;
	}
}
