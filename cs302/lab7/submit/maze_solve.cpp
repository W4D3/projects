#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <set>

using namespace std;

/* maze_solve.cpp
   Mitchell Wade
   October 31th, 2014

   This program reads input in from the cmd.
   line and uses that information to generate
   a graph. Then using depth first search (DFS)
   we enumerate a path through the graph which
   is like finding the path in a maze.
*/

class Node {
    public:
        int id;
        int visited;
        set <int> adj;
};

class Graph {
    public:
        vector <Node *> nodes;
        void Component_Count(int index);
        vector <int> tmp;
};

void Graph::Component_Count(int index) {

    int i;
    Node *n;

    // Set the node
    n = nodes[index];

    // Return if it has been visited
    if (n->visited != 0) {
        return;
    }

    // Mark visited
    n->visited = 1;

    // Push on the path
    tmp.push_back(index);
    
    // If its at the last cell, print the path
    if (n->id == nodes.size()-1) {
        for (i = 0; i < tmp.size(); i++) {
            printf("PATH %d\n", tmp[i]);
        }
        exit(1);
    }

    // Iterate path
    for(set<int>::iterator it = n->adj.begin(); it != n->adj.end(); it++) {
        Component_Count(*it);
    }
    
    // Set the visited flag back to unvisited
    n->visited = 0;
    
    // Pop off the path
    tmp.pop_back();
}

int main() {

    int r, c, i, j, k;
    string junk;
    Node *n;
    Graph g;

    // Read in the number of rows and columns
    cin >> junk >> r >> junk >> c;

    // Print # of ROWS and COLS
    printf("ROWS %d COLS %d\n", r, c);

    // Create the graph
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            n = new Node;
            n->visited = 0;
            n->id = i*c+j;
            g.nodes.push_back(n);
        }
    }

    // Create the edges
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {

            // Set the node
            n = g.nodes[i*c+j];

            // Create a node to the right of the current node
            // if it exists
            if(j < c-1) {
                n->adj.insert(i*c+j+1);
            }

            // Create a node below the current node if it 
            // exists
            if(i < r-1) {
                n->adj.insert((i+1)*c+j);
            }

            // Create a node to the left of the current node 
            // if it exists
            if(j > 0) {
                n->adj.insert(i*c+j-1);
            }

            // Create a node above the current node if it
            // exists
            if(i > 0) {
                n->adj.insert((i-1)*c+j);
            }
        }
    }

    // Read in the walls
    while(cin >> junk >> i >> j) {
        
        printf("WALL %d %d\n", i, j);

        // Simulates adding a wall between nodes
        g.nodes[i]->adj.erase(j);
        g.nodes[j]->adj.erase(i);
    }

    // Call DFS
    g.Component_Count(0);
}
