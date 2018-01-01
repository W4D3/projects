#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Node {
    public:
        int id;
        vector <int> edges;
        int component;
};

class Graph {
    public:
        vector <Node *> nodes;
        void Print();
        void Component_Count(int index, int cn);
};

void Graph::Component_Count(int index, int cn)
{
    Node *n;
    int i;

    n = nodes[index];
    if (n->component != -1) return;
    n->component = cn;
    for (i = 0; i < n->edges.size(); i++) {
        
        printf("Calling Component_Count(%d, %d)\n", n->edges[i], cn);
        Component_Count(n->edges[i], cn);
    }
}

void Graph::Print()
{
    int i, j;
    Node *n;

    for (i = 0; i < nodes.size(); i++) {
        n = nodes[i];
        cout << "Node " << i << ": " << n->component << ":";
        for (j = 0; j < n->edges.size(); j++) {
            cout << " " << n->edges[j];
        }
        cout << endl;
    }
}


main(int argc, char **argv)
{
    Graph g;
    string s;
    int nn, n1, n2, i, c;
    Node *n;

    cin >> s;
    if (s != "NNODES") { cerr << "Bad graph\n"; exit(1); }
    cin >> nn;

    for (i = 0; i < nn; i++) {
        n = new Node;
        n->component = -1;
        n->id = i;
        g.nodes.push_back(n);
    }

    while (!cin.fail()) {
        cin >> s >> n1 >> n2;
        if (!cin.fail()) {
            if (s != "EDGE") { cerr << "Bad graph\n"; exit(1); }
            g.nodes[n1]->edges.push_back(n2);
            g.nodes[n2]->edges.push_back(n1);
        }
    }

    c = 0;
    for (i = 0; i < g.nodes.size(); i++) {
        
        cout << "Main - Node : " << g.nodes[i]->id << endl;

        if (g.nodes[i]->component == -1) {
            c++;

            printf("Main - Calling Component_Count(%d, %d)\n", i, c);
            g.Component_Count(i, c);
        }
    }

    //g.Print();
}
