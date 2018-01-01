#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* chain_heal.c
   Mitchell Wade
   January 24, 2014
   This program reads in a list of players from a battlefield
   and calculates the best way to heal them using chain heal.
   Using a graph data structure we store the input from stdin
   and then traverse the graph using a DFS to find the best
   healing path.
 */

typedef struct node
{
    char *name;
    int x, y, adj_size, visited, ir;
    int cur_PP, max_PP;
    struct node *prev;
    struct node **adj;
	int healing;
} Node;


typedef struct ability
{
    int ir, jr, nj, bh;
    double pr, ip;
    int best_path_length;
    Node **best_path, **final_path;
    int *healing;
} Ability;


void DFS(Node *n, int hop_num, Ability *a, int th, Node *from) {

    int i;
	int ch;				// To store current healing power
	double calcHeal;	// To calculate current healing power
	Node *nn;			// To help store the path

    // Check if has been hopped too
    if (n->visited != -1) return;
    
    // Check if the number of hops is equal to jumps
    if (hop_num == a->nj+1) return;

    // Set it as hopped too
    n->visited = 1;

	// Calculate current amount of healing power
	calcHeal = a->ip;
	for(i = 1; i < hop_num; i++) calcHeal *= (1 - a->pr);
	ch = rint(calcHeal);

    // Calculate total healing 
    if (n->cur_PP + ch <= n->max_PP) {

        // Update total healing by amount currently able to heal
        th += ch;
        n->prev = from;
        n->healing = ch;
        
        // Calculate the best path and set each players healing
		if(th > a->bh && hop_num == a->nj){
			a->bh = th;
			a->best_path_length = hop_num;
			
			nn = n;
			for(i = hop_num-1; i >= 0; i--){
				a->healing[i] = nn->healing;
				a->best_path[i] = nn;
				
				nn = nn->prev;
			}
		} 
	}

	// Calculate total healing 
	else if (n->cur_PP + ch > n->max_PP) {

        // Update total healing by amount currently able to heal
        th += n->max_PP - n->cur_PP;
        n->prev = from;
        n->healing = n->max_PP - n->cur_PP;
        
        // Calculate the best path and set each players healing
		if(th > a->bh && hop_num == a->nj){
			a->bh = th;
			a->best_path_length = hop_num;
			
			nn = n;
			for(i = hop_num-1; i >= 0; i--){
				a->healing[i] = nn->healing;
				a->best_path[i] = nn;

				nn = nn->prev;
			}
		} 
	}

	//DFS on all adj players
	for (i = 0; i < n->adj_size; i++) {
        DFS(n->adj[i], hop_num+1, a, th, n);
	}

    // Calculate the best path and set each players healing
	if(th > a->bh){
		a->bh = th;
		a->best_path_length = hop_num;
		
		nn = n;
		for(i = hop_num-1; i >= 0; i--){
			a->healing[i] = nn->healing;
			a->best_path[i] = nn;

			nn = nn->prev;
		}
	}

	// Reset total healing
	if(n->cur_PP + ch <= n->max_PP) th -= ch;
	else th -= n->max_PP - n->cur_PP;

	// Set it back to not hopped too
	n->visited = -1;

}

int main (int argc, char **argv) {

    char buf[101];
    int i, j, k, initial_range, jump_range, num_jumps, initial_power;
    int X, Y, Current_PP, Max_PP, count, distance, healing;
    int x1, x2, y1, y2, hopNum, total_healed;
    double power_reduction;
    Node *n, *n2, *tmp, *Urgosa;
    Node **array;
    Ability *a;

    // Read in the cmd line
    sscanf(argv[1], "%d", &initial_range);
    sscanf(argv[2], "%d", &jump_range);
    sscanf(argv[3], "%d", &num_jumps);
    sscanf(argv[4], "%d", &initial_power);
    sscanf(argv[5], "%lf", &power_reduction);

    // Allocate memory for global variables
    a = malloc(sizeof(Ability));

    // Store input values in the global struct
    a->ir = initial_range;
    a->jr = jump_range;
    a->nj = num_jumps;
    a->ip = initial_power;
    a->pr = power_reduction;

    // Read in each player
    count = 0;
    while (scanf("%d %d %d %d %s", &X, &Y, &Current_PP, &Max_PP, buf) == 5) {
        n = malloc(sizeof(Node));
        n->x = X;
        n->y = Y;
        n->cur_PP = Current_PP;
        n->max_PP = Max_PP;
        n->name = strdup(buf);
        n->visited = -1;
        n->adj_size = 0;
        if (strcmp(n->name, "Urgosa_the_Healing_Shaman") == 0) Urgosa = n;
        if (count == 0) n->prev = NULL;
        else n->prev = tmp;
        tmp = n;
        count++;

    }

    // Create the array
    array = malloc(sizeof(Node*)*count);

    // Populate the array
    for (i = count-1; i >= 0; i--) {
        array[i] = n;
        n = n->prev;
    }

    // Create the adj list
    for (i = 0; i < count; i++) {
        n = array[i];
        x1 = n->x;
        y1 = n->y;
        for (j = 0; j < count; j++) {
            n2 = array[j];
            if (n != n2) {
                x2 = n2->x;
                y2 = n2->y;

                // Calculate the distance using the distance formula
                distance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
                // Calculate the size of the adj list
                if (distance <= jump_range*jump_range) array[i]->adj_size++;
            }
        }

        // Allocate memory for each player
        n->adj = malloc(sizeof(Node*)*array[i]->adj_size);

        k = 0;
        for (j = 0; j < count; j++) {
            n2 = array[j];
            // Make sure you don't add yourself to the adj list
            if (n != n2) {
                x2 = n2->x;
                y2 = n2->y;

                // Calculate the distance using the distance formula
                distance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));

                // Store each player in the adj list
                if (distance <= jump_range*jump_range) {
                    n->adj[k] = array[j];
                    k++;
                }
            }
        }
    }

    // Calculate the initial range of Urgosa to all players
    x1 = Urgosa->x;
    y1 = Urgosa->y;

    for (i = 0; i < count; i++) {
        tmp = array[i];
        x2 = tmp->x;
        y2 = tmp->y;

        // Calculate the distance using the distance formula
        distance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));

        // Add 1 to the ir variable if the player is in range
        if (distance <= initial_range*initial_range) {
            tmp->ir++;
        }
    }

    // Allocate memory for best path and healing
    a->best_path = malloc(sizeof(Node*)*num_jumps);
    a->final_path = malloc(sizeof(Node*)*num_jumps);
    a->healing = malloc(sizeof(Node*)*num_jumps);


    // DFS
    for (i = 0; i < count; i++) {
        hopNum = 1;
        tmp = array[i];

        // If the player is within range then call DFS
        if (tmp->ir == 1) {
            DFS(array[i], hopNum, a, 0, array[i]);
        }
    }


    // Print out the best path
	total_healed = 0;
    for (i = 0; i < a->best_path_length; i++) { 
        printf("%s %d\n", a->best_path[i]->name, a->healing[i]);
		total_healed += a->healing[i];
	}

    // Print out the total healing
    printf("Total_Healing %d\n", total_healed);

    exit(0);
}
