#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <map>
#include <list>
#include <queue>

using namespace std;

/* worddice.cpp
   Mitchell Wade
   November 14th, 2014

   This program reads in sets of dice with individual letters
   on each side and also reads in a set of words. These are
   represented by nodes and edges are created in between the nodes
   to resemble a graph. Then we use the Edmonds-Karp algorithm to
   search the graph and determine the maximum flow of the graph.
   That flow is how you determine if you can spell the word or not.
   If the flow matches the length of the word then you can spell it.
*/

class Node {
    public: 
        string name;
        int diceID;
        int visited;
        class Edge *backedge;
        vector <class Edge *> adj;
};

class Graph {
    public:
        Graph(vector <string> &, string);
        ~Graph();

        int MaxCap;
        Node *Source;
        Node *Sink;

        vector <Node *> allNodes;
        vector <Node *> allDice; 
        vector <Node *> allLetters; 

        int MaxFlow();
        int Find_Augmenting_Path();
        int BFS();
        vector <Edge *> Path;
};

class Edge {
    public:
        string name;
        Node *to;
        Node *from;
        int residual;
        Edge *reverse;
};

Graph::Graph(vector <string> &Dice, string word) {

    int i, j;
    Node *n;
    Edge *e;

    // Create the source node
    Source = new Node;
    Source->name = "Source";
    allNodes.push_back(Source);

    // Create the sink node
    Sink = new Node;
    Sink->name = "Sink";
    allNodes.push_back(Sink);

    int count = 0;
    // Create the nodes for each dice
    for (i = 0; i < Dice.size(); i++) {
        n = new Node;
        n->name = Dice[i];
        n->visited = -1;
        n->backedge = NULL;
        n->diceID = count++;
        allDice.push_back(n);
        allNodes.push_back(n);
    }

    // Create the sources adj list
    for (i = 0; i < allDice.size(); i++) {
        e = new Edge;
        e->to = allDice[i];
        e->from = Source;
        e->residual = 1;
        e->reverse = new Edge;
        e->reverse->residual = 0;
        e->reverse->reverse = e;
        e->reverse->to = Source;
        e->reverse->from = allDice[i];
        Source->adj.push_back(e);
        allDice[i]->adj.push_back(e->reverse);
    }

    // Create a node for each letter of the word
    for (i = 0; i < word.size(); i++) {
        n = new Node;
        n->name = word[i];
        n->visited = -1;
        n->backedge = NULL;
        allLetters.push_back(n);
        allNodes.push_back(n);
    }

    // Create the sinks adj list
    for (i = 0; i < allLetters.size(); i++) {
        e = new Edge;
        e->to = Sink;
        e->from = allLetters[i];
        e->residual = 1;
        e->reverse = new Edge;
        e->reverse->residual = 0;
        e->reverse->reverse = e;
        e->reverse->to = allLetters[i];
        e->reverse->from = Sink;
        allLetters[i]->adj.push_back(e);
        Sink->adj.push_back(e->reverse);
    }

    // Create edges between the dice and the letters
    for (i = 0; i < allDice.size(); i++) {
        for (j = 0; j < allLetters.size(); j++) {
            if (allDice[i]->name.find(allLetters[j]->name) != string::npos) {
                e = new Edge;
                e->to = allLetters[j];
                e->from = allDice[i];
                e->residual = 1;
                e->reverse = new Edge;
                e->reverse->residual = 0;
                e->reverse->reverse = e;
                e->reverse->to = allDice[i];
                e->reverse->from = allLetters[j];
                allDice[i]->adj.push_back(e);
                allLetters[j]->adj.push_back(e->reverse);
            }
        }
    }

    /*
    // Print out the graph
    for (i = 0; i < allNodes.size(); i++) {
        cout << i << ":" << allNodes[i]->name <<endl;
        for (j = 0; j < allNodes[i]->adj.size(); j++) {
            cout << "  -> " << j << ":" << allNodes[i]->adj[j]->to->name <<endl;
        }
    }
    */
}

Graph::~Graph() {

    int i, j;

    for (i = 0; i < allNodes.size(); i++) {
        for (j = 0; j < allNodes[i]->adj.size(); j++) {
            delete allNodes[i]->adj[j];
        }
        delete allNodes[i];
    }
}

// Calculate the flow of the path
int Graph::MaxFlow() {

    int f;

    MaxCap = 0;
    while (1) {
        f = Find_Augmenting_Path();
        MaxCap += f;
        //printf("Found %d : Total %d\n", f, MaxCap);
        if (f == 0) return MaxCap;
    }
}

// Change the flow on the path
int Graph::Find_Augmenting_Path() {
    
    Node *n;

    if (BFS()) {

        //printf("Found a path\n");
        n = Sink;
        while (n != Source) {
            // Change the edges residual
            n->backedge->residual = 0;
            n->backedge->reverse->residual = 1;

            // Grab the next edge
            n = n->backedge->from;
        }

        return 1;
    }

    return 0;
}

// Check to see if you have a path from the source to the sink
int Graph::BFS() {

    int i;
    Node *n;
    Edge *e;
    queue <Node *> q;

    // Add the first node onto the queue
    q.push(Source);

    for(i = 0; i < allNodes.size(); i++) allNodes[i]->visited = -1;

    // Update the queue while its not empty
    while (!q.empty()) {

        // Grab the first elements name in the queue
        n = q.front();
        //printf("BFS at %s\n", n->name.c_str());

        // If the node that we are about to pop is the Sink
        // return true
        if (n == Sink) return true;

        // Remove the first node from the queue
        q.pop();

        // Add the contents of the Sources adj list to the queue
        for (i = 0; i < n->adj.size(); i++) {
            if (n->adj[i]->to->visited == -1 && n->adj[i]->residual == 1) {
                q.push(n->adj[i]->to);
                n->adj[i]->to->visited = 0;
                n->adj[i]->to->backedge = n->adj[i];
            }
        }
    }

    return false;
}

int main(int argc, char **argv) {

    int i, j;
    ifstream df, wl;
    string dice, word;
    Graph *g;
    Node *n;
    Edge *e;
    vector <string> Dice;

    // Check for proper usage
    if (argc != 3) {
        cerr << "usage: worddice dice-file word-list" <<endl;
        exit(1);
    }

    // Open the dice file stream
    df.open(argv[1]);
    if (df.fail()) {
        cerr << "Couldn't open " << argv[1] << endl;
        exit(1);
    }

    // Store the dice
    while (df >> dice) {
        Dice.push_back(dice);
    }

    // Close the dice file stream
    df.close();

    // Open the word list stream
    wl.open(argv[2]);
    if (wl.fail()) {
        cerr << "Couldn't open " << argv[2] << endl;
        exit (1);
    }

    // Read in each word
    while (wl >> word) {

        // Create the graph
        g = new Graph(Dice, word);

        // If the word length is bigger than the amount
        // of dice that you have then you can't spell it
        if (word.size() > Dice.size()) {
            printf("Cannot spell %s\n", word.c_str());
        }

        // If max flow returns the size of the word
        if (g->MaxFlow() == word.size()) {
            for (i = 0; i < g->allLetters.size(); i++) {
                for (j = 0; j < g->allLetters[i]->adj.size(); j++) {
                    Edge *e;
                    e = g->allLetters[i]->adj[j];
                    //printf("  Edge from %s to %s, residual %d\n", e->from->name.c_str(), e->to->name.c_str(), e->residual);
                    if (g->allLetters[i]->adj[j]->residual == 1) {
                        if(i != 0) printf(",");
                        printf("%d", g->allLetters[i]->adj[j]->to->diceID);
                    }
                }
            }
            printf(": %s\n", word.c_str());
        } else printf("Cannot spell %s\n", word.c_str());

        // Delete the sources adj list
        for (i = 0; i < g->Source->adj.size(); i++) {
            delete g->Source->adj[i];
        }

        // Delete the dice nodes and its adj list
        for (i = 0; i < g->allDice.size(); i++) {
            for (j = 0; j < g->allDice[i]->adj.size(); j++) {
                delete g->allDice[i]->adj[j];
            }
            delete g->allDice[i];
        }

        // Delete the letter nodes and its adj list
        for (i = 0; i < g->allLetters.size(); i++) {
            for (j = 0; j < g->allLetters[i]->adj.size(); j++) {
                delete g->allLetters[i]->adj[j];
            }
            delete g->allLetters[i];
        }

        // Delete the sink adj list
        for (i = 0; i < g->Sink->adj.size(); i++) {
            delete g->Sink->adj[i];
        }
    }

    // Close the word list stream
    wl.close();

    return 0;
}
