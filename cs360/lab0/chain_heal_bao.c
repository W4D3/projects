/*
File: chain_heal.c
Name: Bao Vuu
Course: CS360
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Global struct for DFS and calculate the health
//player node struct
typedef struct node {
    char *name;
    int x, y, k;
    int cur_PP, max_PP;
    struct node *prev;
    int adj_size;
    struct node **adj;
    int heal;
    int visited;
} Node;

typedef struct global {
    int num_jumps;
    int initial_power;
    double power_reduction;
    int best_healing;
    int best_path_length;
    struct node  **best_path;
    int *healing;
} Global;

void DFS (Node *n, int hop, Global *g, int total_healing, Node *from) {

    int i;
    int cur_heal;
    double power;
    Node *nn;

    // If it has been visited, return	
    if (n->visited != -1) return;

    // If you are out of hops, return
    if (hop == g->num_jumps+1) return;

    // Set it to visited
    n->visited = 1;

    //Calculate the healing power
    power = g->initial_power;
    for (i = 1; i < hop; i++) power*=(1-g->power_reduction);
    cur_heal = rint(power);


    if(n->cur_PP + cur_heal <= n->max_PP) {
        total_healing += cur_heal;
        n->prev = from;
        n->heal = cur_heal;

        if (total_healing > g->best_healing && hop == g->num_jumps) {
            g->best_healing = total_healing;
            g->best_path_length = hop;
            nn = n;

            for (i = hop-1; i >= 0; i--) {
                g->healing[i] == nn->heal;
                g->best_path[i] == nn;
                nn = nn->prev;
            }
        }
    } else if (n->cur_PP + cur_heal > n->max_PP) {

        total_healing += n->max_PP - n->cur_PP;
        n->prev = from;
        n->heal = n->max_PP - n->cur_PP;


        if (total_healing > g->best_healing && hop == g->num_jumps) {
            g->best_healing = total_healing;
            g->best_path_length = hop;
            nn = n;

            for (i = hop-1; i >= 0; i--) {
                g->healing[i] == nn->heal;
                g->best_path[i] == nn;
                nn = nn->prev;
            }
        }
    }

    //DFS and paths
    for (i = 0; i < n->adj_size; i++) {
        DFS(n->adj[i], hop+1, g, total_healing, n);
    }

    //checking the current path is the best path?
    if(total_healing > g->best_healing) {
        g->best_healing = total_healing;
        g->best_path_length = hop;
        nn = n;

        for(i = hop-1; i >= 0; i--) {
            g->healing[i] = nn->heal;
            g->best_path[i] = nn;
            nn = nn->prev;
        }
    }

    // Reset total healing
    if (n->cur_PP + cur_heal <= n->max_PP) total_healing -= cur_heal;
    else total_healing -= n->max_PP - n->cur_PP;

    // Set it too not visited
    n->visited = -1;
}

int main (int argc, char **argv) {

    int initial_range, jump_range, num_jumps, initial_power;
    double power_reduction;

    int X, Y;				//x,y coordinate of player
    int Current_PP;			//The player's current health
    int Max_PP;				//The player's max health
    char Name[101];			//The player's name

    int i, j;
    int count, count2, count3;
    double distance;
    distance = 0;
    int rv, x1, x2, y1, y2;

    Node *player, *n;
    Node *Urgosa;
    Node *buffer = NULL;
    Node **temp;
    Global *g;
    //read in command line argument
    sscanf(argv[1], "%d", &initial_range);
    sscanf(argv[2], "%d", &jump_range);
    sscanf(argv[3], "%d", &num_jumps);
    sscanf(argv[4], "%d", &initial_power);
    sscanf(argv[5], "%lf", &power_reduction);

    //put command line argument values into the struct Global
    g = malloc(sizeof(Global));
    g->num_jumps = num_jumps;
    g->initial_power = initial_power;
    g->power_reduction = power_reduction;

    count = 0;
    //store player information to player node linked list
    while (scanf("%d %d %d %d %s", &X, &Y, &Current_PP, &Max_PP, Name) ==5)
    {
        player = malloc(sizeof(Node));
        player->name = strdup(Name);
        player->x = X;
        player->y = Y;
        player->cur_PP = Current_PP;
        player->max_PP = Max_PP;
        player->adj_size = 0;
        player->visited = -1;
        //Find Urgosa and store into a node
        if (strcmp(player->name, "Urgosa_the_Healing_Shaman") == 0) Urgosa = player;
        if (count == 0) player->prev = NULL;
        else player->prev = buffer;
        buffer = player;
        count++;	//count the players

    }

    //allocate array pointer
    temp = malloc(sizeof(Node*)*count);
    for (i = count-1; i >= 0; i--) {
        temp[i] = player;
        player = player->prev;
    }

    /*
    // Create the adj list
    for (i = 0; i < count; i++) {
    x1 = temp[i]->x;
    y1 = temp[i]->y;
    for (j = 0; j < count; j++) {
    if (i != j) {
    x2 = temp[j]->x;
    y2 = temp[j]->y;

    distance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
    if (distance <= jump_range*jump_range) temp[i]->adj_size++;
    }
    }

// Allocate memory for each player
player->adj = malloc(sizeof(Node*)*temp[i]->adj_size);

count2 = 0;
for (j = 0; j < count; j++) {
if (1 != j) {
x2 = temp[j]->x;
y2 = temp[j]->y;

distance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));

if (distance <= jump_range*jump_range) {
temp[i]->adj[count2] = temp[j];
count2++;
}
}
}
}
     */


//create the graph
//calculate the distance by sqrt (x1-x2)^2 + (y1-y2)^2
for (i = 0; i < count; i++) {
    count2 = 0;
    for (j = 0; j < count; j++) {
        if ( i != j ) {
            distance = sqrt(pow(temp[j]->x - temp[i]->x,2) + pow(temp[j]->y - temp[i]->y,2));
            if ( distance <= jump_range ) {
                temp[i]->adj_size++;
            }
        }
    }

    //create another array pointer and store player into, then store in
    //adj list
    temp[i]->adj = malloc(sizeof(Node*)*temp[i]->adj_size);

    for (j = 0; j < count; j++) {
        if ( i != j) {
            distance = sqrt(pow(temp[j]->x - temp[i]->x,2) + pow(temp[j]->y - temp[i]->y,2));
            if ( distance <= jump_range ) {
                temp[i]->adj[count2] = temp[j];
                count2++;

            }
        }
    }
}

//allocate memory for best path and healing
g->best_path = malloc(sizeof(Node*)*num_jumps);
g->healing = malloc(sizeof(Node*)*num_jumps);

/*
// Calculate initial range of players from urgosa
x1 = Urgosa->x;
y1 = Urgosa->y;

for (i = 0; i < count; i++) {
x2 = temp[i]->x;
y2 = temp[i]->y;

// Calculate the distance using the distance formula
distance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));

// Add 1 to the ir variable if the player is in range
if (distance <= initial_range*initial_range) {
temp[i]->k++;
}
}
 */

for (i = 0; i < count; i++) {
    distance = sqrt(pow(Urgosa->x - temp[i]->x,2) + pow(Urgosa->y - temp[i]->y,2));
    if ( distance <= initial_range) {
        temp[i]->k++;

    }
}

// DFS
for (i = 0; i < count; i++) {
    if( temp[i]->k == 1) {
        //DFS call
        DFS(temp[i], 1, g, 0, temp[i]);
    }

}

//print out the path, heal, and total heal
for (i = 0; i < g->best_path_length; i++) {
    printf("%s %d\n",g->best_path[i]->name, g->healing[i]);
}
printf("Total_Healing %d\n", g->best_healing);

exit(0);
}
